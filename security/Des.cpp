#include "Des.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace obotcha {

void _Des::encrypt(File input,File output) {
    fileOperation(encryptMode,input,output);
}

ByteArray _Des::encrypt(ByteArray b) {
    return contentOperation(encryptMode,b);
}

void _Des::decrypt(File input,File output) {
    fileOperation(decryptMode,input,output);
}

ByteArray _Des::decrypt(ByteArray b) {
    return contentOperation(decryptMode,b);
}

void _Des::loadKey(File f) {
    key = f;
}

void _Des::loadKey(String s) {
    key = createFile(s);
}

void _Des::loadKey(const char *s) {
    key = createFile(s);
}

void _Des::genKey(const char *path) {
    genKey(createFile(path));
}

void _Des::genKey(String path) {
    genKey(createFile(path));
}

void _Des::genKey(File f) {
    key = f;
    FILE *key_file = fopen(f->getAbsolutePath()->toChars(), "wb");
    
    unsigned int iseed = (unsigned int)time(NULL);
    srand (iseed);

    short int bytes_written;
    unsigned char* des_key = (unsigned char*) malloc(8*sizeof(char));
    generate_key(des_key);
    bytes_written = fwrite(des_key, 1, DES_KEY_SIZE, key_file);
    if (bytes_written != DES_KEY_SIZE) {
        fclose(key_file);
        free(des_key);
        return;
    }

    free(des_key);
    fclose(key_file);
}

void _Des::fileOperation(int mode,File input,File output) {
    // Read key file
    if(key == nullptr || !key->exists()) {
        printf("trace1 \n");
        return;
    }

    FILE *key_file = fopen(key->getAbsolutePath()->toChars(), "rb");
    if (!key_file) {
        printf("trace2 \n");
        return;
    }

    short int bytes_read;
    unsigned short int padding; 
    unsigned char* des_key = (unsigned char*) malloc(8*sizeof(char));
    bytes_read = fread(des_key, sizeof(unsigned char), DES_KEY_SIZE, key_file);
    if (bytes_read != DES_KEY_SIZE) {
        fclose(key_file);
        free(des_key);
        printf("trace3 \n");
        return;
    }
    
    fclose(key_file);

    // Open input file
    FILE *input_file = fopen(input->getAbsolutePath()->toChars(), "rb");
    if (!input_file) {
        printf("trace4 \n");
        return;
    }

    // Open output file
    FILE *output_file = fopen(output->getAbsolutePath()->toChars(), "wb");
    if (!output_file) {
        printf("trace5 \n");
        return;
    }

    // Generate DES key set
    short int bytes_written, process_mode;
    unsigned long block_count = 0, number_of_blocks;
    unsigned char* data_block = (unsigned char*) malloc(8*sizeof(char));
    unsigned char* processed_block = (unsigned char*) malloc(8*sizeof(char));
    key_set* key_sets = (key_set*)malloc(17*sizeof(key_set));

    //start = clock();
    generate_sub_keys(des_key, key_sets);
    //finish = clock();
    //time_taken = (double)(finish - start)/(double)CLOCKS_PER_SEC;

    
    // Get number of blocks in the file
    fseek(input_file, 0L, SEEK_END);
    unsigned long file_size = ftell(input_file);

    fseek(input_file, 0L, SEEK_SET);
    number_of_blocks = file_size/8 + ((file_size%8)?1:0);

    printf("trace6 \n");
    //start = clock();
    // Start reading input file, process and write to output file
    while(fread(data_block, 1, 8, input_file)) {
        block_count++;
        if (block_count == number_of_blocks) {
            if (mode == encryptMode) {
                padding = 8 - file_size%8;
                if (padding < 8) { // Fill empty data block bytes with padding
                    memset((data_block + 8 - padding), (unsigned char)padding, padding);
                }

                process_message(data_block, processed_block, key_sets, mode);
                bytes_written = fwrite(processed_block, 1, 8, output_file);

                if (padding == 8) { // Write an extra block for padding
                    memset(data_block, (unsigned char)padding, 8);
                    process_message(data_block, processed_block, key_sets, mode);
                    bytes_written = fwrite(processed_block, 1, 8, output_file);
                }
            } else {
                process_message(data_block, processed_block, key_sets, mode);
                padding = processed_block[7];

                if (padding < 8) {
                    bytes_written = fwrite(processed_block, 1, 8 - padding, output_file);
                }
            }
        } else {
            process_message(data_block, processed_block, key_sets, mode);
            bytes_written = fwrite(processed_block, 1, 8, output_file);
        }
        memset(data_block, 0, 8);
    }

    //finish = clock();

    // Free up memory
    free(des_key);
    free(data_block);
    free(processed_block);
    fclose(input_file);
    fclose(output_file);
    free(key_sets);

    // Provide feedback
    //time_taken = (double)(finish - start)/(double)CLOCKS_PER_SEC;
    
}
    
ByteArray _Des::contentOperation(int mode,ByteArray content) {
    // Read key file
    if(key == nullptr || !key->exists()) {
        return nullptr;
    }

    FILE *key_file = fopen(key->getAbsolutePath()->toChars(), "rb");
    if (!key_file) {
        return nullptr;
    }

    short int bytes_read;
    unsigned char* des_key = (unsigned char*) malloc(8*sizeof(char));
    bytes_read = fread(des_key, sizeof(unsigned char), DES_KEY_SIZE, key_file);
    if (bytes_read != DES_KEY_SIZE) {
        fclose(key_file);
        free(des_key);
        return nullptr;
    }
    
    fclose(key_file);

    key_set* key_sets = (key_set*)malloc(17*sizeof(key_set));
    //start = clock();
    generate_sub_keys(des_key, key_sets);

    unsigned long block_count = 0, number_of_blocks;
    unsigned char* processed_block = (unsigned char*) malloc(8*sizeof(char));
    number_of_blocks = content->size()/8 + ((content->size()%8)?1:0);

    ByteArray output = createByteArray(content->size());
    ByteArray input = createByteArray(content);
    unsigned char *data_block = (unsigned char *)input->toValue();
    unsigned char *out_block = (unsigned char *)output->toValue();
    // Start reading input file, process and write to output file

    unsigned short int padding;

    while(block_count != number_of_blocks) {
        block_count++;
        if (block_count == number_of_blocks) {
            if (mode == encryptMode) {
                padding = 8 - content->size()%8;
                if (padding < 8) { // Fill empty data block bytes with padding
                    memset((data_block + 8 - padding), (unsigned char)padding, padding);
                }

                process_message(data_block, processed_block, key_sets, mode);
                //bytes_written = fwrite(processed_block, 1, 8, output_file);
                memcpy(out_block,processed_block,8);
                out_block += 8;

                if (padding == 8) { // Write an extra block for padding
                    memset(data_block, (unsigned char)padding, 8);
                    process_message(data_block, processed_block, key_sets, mode);
                    //bytes_written = fwrite(processed_block, 1, 8, output_file);
                    memcpy(out_block,processed_block,8);
                    out_block += 8;
                }
            } else {
                process_message(data_block, processed_block, key_sets, mode);
                padding = processed_block[7];

                if (padding < 8) {
                //    bytes_written = fwrite(processed_block, 1, 8 - padding, output_file);
                    memcpy(out_block,processed_block,8 - padding);
                    out_block += 8 - padding;
                }
            }
        } else {
            process_message(data_block, processed_block, key_sets, mode);
            //bytes_written = fwrite(processed_block, 1, 8, output_file);
            memcpy(out_block,processed_block,8);
            out_block += 8;
        }
        //memset(data_block, 0, 8);
        data_block += 8;
    }

    //finish = clock();

    // Free up memory
    free(des_key);
    //free(data_block);
    free(processed_block);
    free(key_sets);
    //fclose(input_file);
    //fclose(output_file);

    // Provide feedback
    //time_taken = (double)(finish - start)/(double)CLOCKS_PER_SEC;
    return output;
}


}
