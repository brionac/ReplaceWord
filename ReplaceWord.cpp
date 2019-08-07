#include <iostream>
#include <cstdlib>
using namespace std;

class Replacer
{
    public:
        Replacer()
        {
            this->WordExist = false;
            this->Childs = NULL;
        };
        
        ~Replacer()
        {
            if (!this->Childs)
            {
                return;
            }
            for(int i=0;i<256;i++)
            {
                delete this->Childs[i];
            }
        }
        
        void ReloadSingleWord(char* word)
        {
            int l = strlen(word);
            Replacer* p = this;
            
            for(int i=0;i<l;i++)
            {
                if (!(p->Childs))
                {
                    p->Childs = new Replacer*[256];
                    for(int j=0;j<256;j++)
                    {
                        p->Childs[j] = new Replacer();
                    }
                }
                unsigned char t = (unsigned char)(word[i]);
                
                p = p->Childs[t];
            }
            p->WordExist = true;
        }
        
        void CheckSingleWord(string &word, char ReplaceTo = '*')
        {
            int l = word.size();
            int i = 0;
            
            while(i<l)
            {
                int r = this->CheckSingleWordFrom(word, i);
                if (r > 0)
                {
                    for(int t=i;t<=r;t++)
                    {
                        word[t] = ReplaceTo;
                    }
                    i = r+1;
                }
                else
                {
                    i++;
                }
            }
        }
    
    private:
        
        int CheckSingleWordFrom(string word, int index)
        {
            int l = word.size();
            Replacer *p = this;
            
            int dest = index;
            while(dest < l)
            {
                unsigned char c = (unsigned char)(word[dest]);
                
                if (p->Childs[c]->WordExist)
                {
                    return dest;
                }
                if (!(p->Childs[c]->Childs))
                {
                    return -1;
                }
                dest++;
                p = p->Childs[c];
            }
            
            return -1; 
        }
        
        bool WordExist;
        Replacer **Childs;
};

int main()
{
    Replacer *trie = new Replacer();
    
    trie->ReloadSingleWord("aa");
    trie->ReloadSingleWord("操"); 
    trie->ReloadSingleWord("你马"); 
    
    string k = "aaaaaA你操作你马呢？";
    trie->CheckSingleWord(k, '?');
    
    cout<<k<<endl;
    /*
        It will output:
        ????aA你??作????呢？
    */

    delete trie;
    system("pause");
    return 0;
}
