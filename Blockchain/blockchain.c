#include "blockchain.h"

void set_digest(struct Digest* digest, struct Block* block){
    BYTE* temp = SHA_40((BYTE*)block,BLOCK_SIZE);
    digest->hash0 = temp[0];
    digest->hash0 = temp[1];
    digest->hash0 = temp[2];
    digest->hash0 = temp[3];
    digest->hash0 = temp[4];
}

void add(struct Blockchain* chain, int data){
    struct Block* newBlock = (struct Block*)malloc(BLOCK_SIZE);
    if(chain->size==0){
        newBlock->height = 0;
        newBlock->data = data;
        newBlock->prev_hash.hash0 = 0;
        newBlock->prev_hash.hash1 = 0;
        newBlock->prev_hash.hash2 = 0;
        newBlock->prev_hash.hash3 = 0;
        newBlock->prev_hash.hash4 = 0;
        newBlock->prev_block = NULL;
        chain->head = newBlock;
    }
    if(chain->size>=1){
        newBlock->height = chain->head->height + 1;
        newBlock->data = data;
        BYTE* blockHash = SHA_40((BYTE*)chain->head,BLOCK_SIZE);
        newBlock->prev_hash.hash0 = blockHash[0];
        newBlock->prev_hash.hash1 = blockHash[1];
        newBlock->prev_hash.hash2 = blockHash[2];
        newBlock->prev_hash.hash3 = blockHash[3];
        newBlock->prev_hash.hash4 = blockHash[4];
        newBlock->prev_block = chain->head;
        chain->head = newBlock;
    }
    chain->size++;
}


void verify(struct Blockchain* chain){
    struct Block* currentBlock = chain->head;
    int verfifiedBlocks = 0;
    printf("Verifying . . .\n");
    while(currentBlock){
        for(int i = chain->size-1; i >= 0;i--){
            if(currentBlock->height==0){
                //at the bottom
                int result = (currentBlock->prev_hash.hash0 == 0) &&
                             (currentBlock->prev_hash.hash1 == 0) &&
                             (currentBlock->prev_hash.hash2 == 0) &&
                             (currentBlock->prev_hash.hash3 == 0) &&
                             (currentBlock->prev_hash.hash4 == 0);
                if(result==0){
                    printf("Block %d has failed.\n",i);
                    break;
                }
                printf("Block %d has passed.\n",i);
                verfifiedBlocks++;
            }
            else{
                BYTE* computedHash = SHA_40((BYTE*)currentBlock->prev_block,BLOCK_SIZE);
                int result = (currentBlock->prev_hash.hash0 == computedHash[0]) &&
                             (currentBlock->prev_hash.hash1 == computedHash[1]) &&
                             (currentBlock->prev_hash.hash2 == computedHash[2]) &&
                             (currentBlock->prev_hash.hash3 == computedHash[3]) &&
                             (currentBlock->prev_hash.hash4 == computedHash[4]);
                if(result==0){
                    printf("Block %d has failed.\n",i);
                    break;
                }
                printf("Block %d has passed.\n",i);
                verfifiedBlocks++;
            }
            currentBlock = currentBlock->prev_block;
        }
        if(verfifiedBlocks==chain->size){
            printf("All blocks have been verified.\n");
        }
        break;
    }
}






void alter_block(struct Blockchain* chain, int height, int data){
    struct Block* currentBlock = chain->head;
    printf("Altering a block . . .\n");
    printf("Block %d altered containing now %d\n",height,data);
    while(currentBlock){
        for(int i = chain->size; i >= 0; i--){
            if(currentBlock->height==height){
                currentBlock->data = data;
                break;
            }
            if(height!=0 && currentBlock->height!=height){
                currentBlock = currentBlock->prev_block;
            }
            if(currentBlock->height==0){
                break;
            }
        }
        break;
    }
}


void alter_2_blocks(struct Blockchain* chain, int height, int data){
    struct Block* currentBlock = chain->head;
    printf("Altering 2 blocks . . .\n");
    printf("Block %d altered containing now %d\n",height,data);
    printf("Block %d altered too.\n",height+1);
    while(currentBlock){
        for(int i = chain->size; i >= 0; i--){
            if(currentBlock->height==height){
                currentBlock->data = data;
                break;
            }
            if(height!=0 && currentBlock->height!=height){
                currentBlock = currentBlock->prev_block;
            }
            if(currentBlock->height==0){
                break;
            }
        }
        break;
    }
    currentBlock = chain->head;
    while(currentBlock){
        for(int i = chain->size; i>=0; i--){
            if(currentBlock->height==height+1){
                BYTE* temp = SHA_40((BYTE*)currentBlock->prev_block,BLOCK_SIZE);
                currentBlock->prev_hash.hash0 = temp[0];
                currentBlock->prev_hash.hash1 = temp[1];
                currentBlock->prev_hash.hash2 = temp[2];
                currentBlock->prev_hash.hash3 = temp[3];
                currentBlock->prev_hash.hash4 = temp[4];
            }
        }
        break;
    }
}


void delete_at(struct Blockchain* chain, int height){
    struct Block* currentBlock = chain->head;
    printf("Deleting . . .\n");
    printf("Block %d deleted.\n",height);
    for(int i = chain->size; i >= 0; i--){
        if (currentBlock->height==height+1){
            struct Block* deletingBlock = currentBlock->prev_block;
            currentBlock->prev_block = deletingBlock->prev_block;
        }
        if(height!=0 && currentBlock->height!=height){
            currentBlock = currentBlock->prev_block;
        }
        if(currentBlock->height==0){
            break;
        }
    }
}


/*
 * Name: initialize
 * Purpose: Creates and returns a pointer to an empty blockchain
 * Parameters: None
 * Returns: pointer to Blockchain
 */
struct Blockchain* initialize()
{
    struct Blockchain* chain = (struct Blockchain*)malloc(sizeof(struct Blockchain));
    chain->size = 0;
    chain->head = NULL;
    return chain;
}


/*
 * Name: print_blockchain
 * Purpose: Prints blockchain
 * Parameters: Pointer to Blockchain
 * Returns: None
 */
void print_blockchain(struct Blockchain* blockchain)
{
    printf("Printing...\n");
    struct Block* current = blockchain->head;
    while(current){
        printf("{height: %d, data: %d, prev_hash: %d %d %d %d %d}\n",
        current->height, current->data, current->prev_hash.hash0, current->prev_hash.hash1,
        current->prev_hash.hash2, current->prev_hash.hash3, current->prev_hash.hash4);
        current = current->prev_block;
    }
}


/*
 * Name: main
 * Purpose: Test functions above
 * Parameters: int argc, char* argv[]
 * Returns: integer
 */
int main(int argc, char* argv[])
{
    //Test cases
    //Test 1
    //Create, print, and verify blockchain
    struct Blockchain* blockchain = initialize();
    for (int i = 1; i <= 5; i++)
    {
        add(blockchain, 10*i);
    }
    print_blockchain(blockchain);
    verify(blockchain);
   
   


    //Test 2
    //Alter the value in a block, print, and verify blockchain
    // alter_block(blockchain, 2, 300);
    // print_blockchain(blockchain);
    // verify(blockchain);




    //Test 3
    //Comment out Test 2, and uncomment the following three code lines
    //Alter the value in a block and the hash value tracked for
    //that altered block
    // alter_2_blocks(blockchain, 1, 200);
    // print_blockchain(blockchain);
    // verify(blockchain);


    //Test 4
    //Comment out Test 2 and 3, and uncomment the following three code lines
    // delete_at(blockchain, 1);
    // print_blockchain(blockchain);
    // verify(blockchain);


    return 0;
}

