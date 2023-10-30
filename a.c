// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <dirent.h>
// #include <sys/stat.h>

// void listFiles(const char *path, int indent)
// {
// 	struct dirent *entry;
// 	DIR *dir = opendir(path);

//     if (dir == NULL)
// 	{
//         perror("Opendir:");
//         return;
//     }

// 	while ((entry = readdir(dir)) != NULL)
// 	{
// 		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
// 		{
// 			for (int i = 0; i < indent; i++)
// 				printf ("  ");
// 			printf ("%s\n", entry->d_name);
// 			char new_path[PATH_MAX];
// 			snprintf (new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
// 			struct stat st;
// 			if (stat (new_path, &st) == 0 && S_ISDIR(st.st_mode))
// 				listFiles (new_path, indent + 1);
// 		}
//     }

// 	closedir(dir);

// }

// int main(int argc, char *argv[]) 
// {
// 	const char *path = (argc > 1) ? argv[1] : "."; // Default to the current directory if no path is provided.
// 	printf("%s\n", path);

//     listFiles(path, 0);

//     return 0;
// }
