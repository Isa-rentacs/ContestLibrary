
/* Pass to std::sort */
bool predication(const int &a, const int &b){
    return a < b;
}

/* or override operator< */
class SomeClass{
public:
    SomeClass(int a, int b){
        id = a;
        score = b;
    }
    int id;
    int score;

    bool operator < (const SomeClass &arg) const{
        if(score == arg.score){
            return id < arg.id;
        }else{
            return score > arg.score;
        }
    }
};