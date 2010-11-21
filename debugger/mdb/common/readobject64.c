#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mdb_modapi.h>
#include <stab.h>

#include <stab_parser.h>

unsigned char *read_section_names(int fd, Elf64_Ehdr *);
int read_stab_entries(int fd, Elf64_Ehdr *h, unsigned char *buffer);


extern struct stab_entry *stabs_list_tail;
extern struct stab_entry *stabs_list_head;

int read_object(char *filename)
{
	Elf64_Ehdr elf_header;
	int fd=-1;
	unsigned char *buffer;
	int ret;


	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		printf("Unable to open input object file \n");
		return DCMD_ERR;
	}

	if (read(fd, &elf_header, sizeof(Elf64_Ehdr))!= sizeof(Elf64_Ehdr)) {	
		printf("Unable to read elf header\n");
		return DCMD_ERR;
	}
	
	if ((elf_header.e_ident[EI_MAG0] != 0x7f) ||
		(elf_header.e_ident[EI_MAG1] != 'E') ||
		(elf_header.e_ident[EI_MAG2] != 'L') ||
		(elf_header.e_ident[EI_MAG3] != 'F')) {
		printf("Not a valid elf file\n");
		return DCMD_ERR;
	}

	if (elf_header.e_ident[EI_CLASS] != ELFCLASS64) {
		printf("The specific object is not 64 bit\n");
		return DCMD_ERR;
	}

	if (!((elf_header.e_ident[EI_OSABI] == ELFOSABI_SOLARIS) || 
		(elf_header.e_ident[EI_OSABI] == 0x00))) {
		printf("This is not solaris binary 0x%02x\n", elf_header.e_ident[EI_OSABI]);
		return DCMD_ERR;
	}

	if (elf_header.e_machine != EM_SPARCV9) {
		printf("This is not sparcv9 binary\n");
		return DCMD_ERR;
	}

	printf("We are reading correct binary :)\n");
	buffer=read_section_names(fd, &elf_header);
	ret = read_stab_entries(fd, &elf_header, buffer);
	close(fd);
	return ret;
}

unsigned char *read_section_names(int fd, Elf64_Ehdr *h)
{
	int offset;
	Elf64_Shdr section;
	unsigned char *buffer= NULL;

	offset = h->e_shoff + h->e_shentsize * h->e_shstrndx;
	lseek(fd, offset, SEEK_SET);
	read(fd, &section, sizeof(Elf64_Shdr));

	buffer = (unsigned char *)mdb_zalloc(section.sh_size, UM_SLEEP);
	
	if (buffer == NULL) {
		printf("Unable to allocate memory for data size=%d\n", section.sh_size);
		return NULL;
	}
	
	lseek(fd, section.sh_offset, SEEK_SET);
/*	printf("address of buffer is =%p reading string table of size = %d\n", buffer, 
				section.sh_size);a
*/
	if (read(fd, buffer, section.sh_size) != section.sh_size) {
		printf("Error reading string table\n");
		free(buffer);
		return NULL;
	}
	return buffer;
}

int read_stab_entries(int fd, Elf64_Ehdr *header, unsigned char *buffer)
{
    int i=0;
    Elf64_Shdr *section;
	Elf64_Shdr *stab_section, *stabstr_section;
	struct stab stab;
	unsigned char *stabstr_buf;
	int num_entries;
	struct stab_entry *entry;
	
	stab_section = NULL;
	stabstr_section = NULL;

    section = (Elf64_Shdr*)mdb_zalloc(sizeof(Elf64_Shdr), UM_SLEEP);

    lseek(fd, header->e_shoff, SEEK_SET);
    for (i=0; i < header->e_shnum; i++) {
        read(fd, section, sizeof(Elf64_Shdr));
        if (strcmp((char*)(buffer + section->sh_name), ".stab.excl")==0) {
            stab_section = section;
			break;
		}
    }

	if (stab_section == NULL) {
		printf("No debugging information found\n");
		return -1;
	}

	section = (Elf64_Shdr*)mdb_zalloc(sizeof(Elf64_Shdr), UM_SLEEP);
    lseek(fd, header->e_shoff, SEEK_SET);
    for (i=0; i < header->e_shnum; i++) {
        read(fd, section, sizeof(Elf64_Shdr));
        if (strcmp((char*)(buffer + section->sh_name), ".stab.exclstr")==0) {
            stabstr_section = section;
			break;
		}
    }
	if (stabstr_section == NULL) {
		printf("No debugging information found\n");
		return -1;	
	}
	stabstr_buf = (unsigned char *)mdb_alloc(stabstr_section->sh_size, UM_SLEEP);		
	lseek(fd, stabstr_section->sh_offset, SEEK_SET);
	read(fd, stabstr_buf, stabstr_section->sh_size);

	lseek(fd, stab_section->sh_offset, SEEK_SET);		
	num_entries = stab_section->sh_size / stab_section->sh_entsize;
	printf("Number of stab entries are %d\n", num_entries);
	i=0;
	while (i<num_entries)
 	{
		read(fd, &stab, sizeof(struct stab));
		if (stab.n_type != 128) {
			i++;
			continue;
		}

		entry = (struct stab_entry *)mdb_zalloc(sizeof(struct stab_entry), UM_SLEEP);
		entry->type = stab.n_type;
		entry->other = stab.n_other;
		entry->desc = stab.n_desc;
		entry->value = stab.n_value;
		entry->str = (stabstr_buf + stab.n_strx);

		add_stab_entry(entry);
		i++;
	}

    init_type_table();
    entry = stabs_list_head;
    while (entry != NULL) {
		 /* printf("%s\n", entry->str); */
        parse_stab_entry(entry);
        entry = entry->next;
    }

    process_forward_refs();
	free_stab_entry_list();
	mdb_free(stabstr_buf, stabstr_section->sh_size);
	mdb_free(stab_section, sizeof(Elf64_Shdr));
	mdb_free(stabstr_section, sizeof(Elf64_Shdr));
	return 0;
}

