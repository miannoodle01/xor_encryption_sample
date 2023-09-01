#include "../includes/includes.h"


int main(int argc, char* argv[]) {

    char* inFileName = NULL;
    char* outFileName = NULL;
    char* key = NULL;

    if (getArgs(argc, argv, inFileName, key, outFileName) == -1) {

        exit(EXIT_FAILURE);
    
    }

    return 0;

}

int getArgs(int argc, char* argv[], char* inFileName, char* key, char* outFileName) {
    
    char inputInvalid[56] = "Input is invalid, type \"./xorSample --help\" for usage.\n";

    /* uncomment the following if you want to see args */
    //for (int i = 0; i < argc; i++) {
    //    printf("argv[%i] = %s\n", i, argv[i]);
    //}

    if (argc != 9) {

        if (
            (argc == 2)&&
            (argv[2] == NULL)&&
            (strcmp(argv[1], "--help") == 0)
        ) {

            helpMsg();
            return 0;

        } else {

            printf(inputInvalid);
            return -1;

        }

    } else {
        int opMode = 0; // 0 == encrypt && 1 == decrypt
        int i = 1;
        
        while (i < 9) {

            if (strcmp(argv[i], "--input") == 0) {

                i++;
                inFileName = argv[i];
                i++;

            } else if (strcmp(argv[i], "--output") == 0) {

                i++;
                outFileName = argv[i];
                i++;

            } else if (strcmp(argv[i], "--key") == 0) {

                i++;
                key = argv[i];
                i++;

            } else if (strcmp(argv[i], "--mode") == 0) {

                i++;

                if (strcmp(argv[i], "encrypt") == 0) {

                    opMode = 0;

                } else if (strcmp(argv[i], "decrypt") == 0) {

                    opMode = 1;

                }
                
                i++;

            } else {

                printf(inputInvalid);
                return -1;
            
            }

        }

        if (opMode == 0) {
            
            if (access(inFileName, F_OK) == 0) {
                
                encDecFile(inFileName, key, outFileName);

            } else {

                printf("File does not exists or app does not have permission to access it.\n");
                return -1;

            }
            
        } else {

            int k = access(inFileName, F_OK);
            if (k == 0) {
                
                encDecFile(inFileName, key, outFileName);

            } else {

                printf("File does not exists or app does not have permission to access it.\n");
                return -1;

            }

        }
        

    }
    
    return 0;
}

int encDecFile(char* inFileName, char* key, char* outFileName) {

    int ch;
    FILE* fpIn;
    FILE* fpOut;
    fpIn = fopen(inFileName, "r");
    fpOut = fopen(outFileName, "w");
    
    while((ch = fgetc(fpIn)) != EOF) {
        
        ch ^= *key;
        fputc(ch, fpOut);

    }

    fclose(fpIn);
    fclose(fpOut);

    return 0;
    
}

void helpMsg() {

    printf(
        "xorSample - File Encryption/Decryption Tool\n"
        "Usage: ./xorSample [options]\n"
        "Options:\n"
        "  --input <filename>   Input file to be encrypted/decrypted\n"
        "  --output <filename>  Output file after encryption/decryption\n"
        "  --key <key>          Encryption/Decryption key\n"
        "  --mode <mode>        Operation mode: 'encrypt' or 'decrypt'\n"
        "  --help               Display this help message\n"
    );
    
}
