template<int size>
class StaticDictionary{
    public:
    int StoreWord(std::string str){
        std::string * adr = sm.Request();

        // check if space available
        if (adr != nullptr){
            *adr = str;

            //add the address to the vector
            //Only the addresses are saved here
            adrVector.push_back(adr);
            return 1;
        }
        return 0;
    }

    void ListWords(){
        std::map<std::string, int> stringMap;

        //populate order map O(logn)
        for (auto adr : adrVector){
            stringMap[*adr]++;
        } 

        for (auto str : stringMap){
            std::cout<< str.first<< " " << str.second<< std::endl;
        }
    }

    void releaseWord(std::string toRel){
         for (auto  i = adrVector.begin(); i != adrVector.end(); i++)
         {
             // find the adress and release it
             if(**i == toRel){
                 sm.Return(*i);
                 adrVector.erase(i);
                 return;
             }
         }
    } 
    

    private:
    StaticMemPool<std::string,size> sm;
    std::vector<std::string*> adrVector; 

};
int main(){
    StaticDictionary<10> dict;
    dict.StoreWord("bbc");
    dict.StoreWord("aaa");
    dict.StoreWord("aaa");
    dict.StoreWord("aaa");
    dict.releaseWord("aaa");
    dict.StoreWord("bb");
    dict.StoreWord("bb");
    dict.StoreWord("bbc");
    dict.ListWords();
   
// output:
// aaa 2
// bb 2
// bbc 2
}
