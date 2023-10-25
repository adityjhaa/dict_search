// Do NOT add any other includes
#include "dict.h"
#define SIZE 300023

char to_lower(char c){
    return c - 'A' + 'a';
}

int hash_val(string id){

    int hashkey =0;
    int pow = 1;
    
    for(char ch : id){
        hashkey = (hashkey + ch*pow)%SIZE;
        pow = (pow*37)%SIZE;
    }

    return hashkey;
}

Dict::Dict(){
   words_HashTable.resize(SIZE); 
}

Dict::~Dict(){
    // Implement your function here    
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    int i = 0;
    int cnt = 0;
    while(i<sentence.size()){
        string temp="";
        if(sentence[i]==' ' or sentence[i]=='.'){
            i++;
        }else{
            cnt = i;
            while(sentence[i]!=' ' and sentence[i] !='.'){
                if(sentence[i]>='A' and sentence[i]<='Z'){
                    sentence[i] = to_lower(sentence[i]);
                }
                temp += sentence[i];
                i++;
            }
        }
        if(temp!=""){
            int hash = hash_val(temp);
            
            bool flag = false;//to check if the word if present

            for(int j = 0; j < words_HashTable[hash].size(); j++){
                if(words_HashTable[hash][j].first==temp){
                    //word is present
                    words_HashTable[hash][j].second.add_instance(book_code,page,paragraph,sentence_no,cnt);
                    flag = true;
                }
            }
            if(flag==false){
                //word isn't present
                //create and insert
                word_instance curr;
                curr.add_instance(book_code,page,paragraph,sentence_no,cnt);
                words_HashTable[hash].push_back({temp,curr});
                
                //insert in sorted data structure
                if(working.size()==0){
                    working.push_back(temp);
                }else{
                    if(temp>working[working.size()-1]){
                        working.push_back(temp);
                    }else{
                        int m=0;
                        while(m<working.size()){
                            if(working[m]>temp){
                                working.insert(working.begin()+m,temp);
                                break;
                            }
                            m++;
                        }
                    }
                }
            }
        }

    }
    return;
}

int Dict::get_word_count(string word){
    
    for(int i = 0; i<word.size(); i++){
        if(word[i]>='A' and word[i]<='Z'){
            word[i] = to_lower(word[i]);
        }
    }

    int hash = hash_val(word);
    for(int j = 0; j < words_HashTable[hash].size(); j++){
        if(words_HashTable[hash][j].first==word){
            //word is present
            return words_HashTable[hash][j].second.offset.size();            
        }
    }
    return -1;
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    
    
    ofstream output(filename);
    for(int i = 0; i<working.size();i++){
        output << working[i]<<", " << get_word_count(working[i])<<endl;
    }
    output.close();
    return;
}
