#include "hash.h"


/*Even after going to office hours, prof. Brigden told me to hard code sizes into my SHA_40 function. When I was
trying to use strlen, it was coming up with errors.
*/


BYTE* SHA_40(const BYTE* data, size_t size){
   
    BYTE A = 11;
    BYTE B = 22;
    BYTE C = 33;
    BYTE D = 44;
    BYTE E = 55;
    for(int i = 0; i<size;i++){
        for(int r = 0; r<12;r++){
            BYTE Aout = 0;
            BYTE Bout = 0;
            BYTE Cout = 0;
            BYTE Dout = 0;
            BYTE Eout = 0;


            //Compute A output


            Aout = r + data[i] + (A>>3) + ((B & C) ^ D) + E;


            //Compute B output


            Bout = A;


            //Compute C output


            Cout = B << 1;


            //Compute D output


            Dout = C;


            //Compute E output


            Eout = D;


            //New output
            A = Aout;
            B = Bout;
            C = Cout;
            D = Dout;
            E = Eout;
        }
    }
    struct Digest* tmp = (struct Digest*)malloc(DIGEST_SIZE * sizeof(BYTE));
    tmp->hash0=A;
    tmp->hash1=B;
    tmp->hash2=C;
    tmp->hash3=D;
    tmp->hash4=E;
    return (BYTE*)tmp;
}


int digest_equal(struct Digest* digest1, struct Digest* digest2){
    int answer = (digest1==digest2);
    if(answer==1){
        printf("Digest 1 and Digest 2 are equal.\n\n");
        return 1;
    }
    else{
        printf("Digest 1 and Digest 2 are not equal.\n\n");
        return 0;
    }
}


int main(){
    printf("\n\n");
    BYTE str1[] = "Rob";
    BYTE* first = SHA_40(str1,3);
    printf("%d %d %d %d %d\n\n",first[0],first[1],first[2],first[3],first[4]);


    BYTE str2[] = "James";
    BYTE* second = SHA_40(str2,5);
    printf("%d %d %d %d %d\n\n",second[0],second[1],second[2],second[3],second[4]);


    BYTE str3[] = "Ahmed";
    BYTE* third = SHA_40(str3,5);
    printf("%d %d %d %d %d\n\n",third[0],third[1],third[2],third[3],third[4]);
   
    BYTE str4[] = "CSEC";
    BYTE* fourth = SHA_40(str4,4);
    printf("%d %d %d %d %d\n\n",fourth[0],fourth[1],fourth[2],fourth[3],fourth[4]);
   
    BYTE str5[] = "Mason";
    BYTE* fifth = SHA_40(str5,5);
    printf("%d %d %d %d %d\n\n",fifth[0],fifth[1],fifth[2],fifth[3],fifth[4]);


    printf("Rob == Rob: ");
    digest_equal((struct Digest*)first,(struct Digest*)first);
    printf("James == Ahmed: ");
    digest_equal((struct Digest*)second,(struct Digest*)third);
    return 0;
}



