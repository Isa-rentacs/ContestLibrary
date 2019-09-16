#include <string>
#include <vector>
// Z-algorithm
// For a given string S, return an array A[i] such that
// A[i] := Length of longest common prefix of S and S[i:]

vector<int> zalgo(string& s)
{
    int len = s.length();
    vector<int> ret(len);
    ret[0] = len;
    int start = 1;
    int length = 0;
    while(start < len)
    {
        // i -> start
        // j -> length
        // Start from i, incrementally search j such that S[0:j] == S[i:i+j]
        while(start + length < len && s[length] == s[start+length]) ++length;
        ret[start] = length;

        // If S[0] != S[i], increment i
        if(length == 0) 
        {
            ++start;
            continue;
        }
        
        //           k                                i
        // <----------------------------------------S--------------------------------------->
        // <----- S' (length == j) ----->             <----- S' (length == j) ----->
        // (Case.1) In case of offset + ret[offset] < length
        // <-offset-><--ret[k] prefix-->              <-offset-><--ret[k] prefix-->
        // <--ret[k] prefix--> (as ret[k] is the length of the longest prefix)
        //                                                      ret[i+k] = ret[k]
        //
        // (Case.2) In case of offset + ret[offset] >= length
        // <-offset-><--- ret[k] prefix --->          <-offset-><--- ret[k] prefix --->
        //                                                                         ^
        //                       Up to here, it's guaranteed ret[k] is a prefix of S
        // Therefore, increment i = i + offset, length = length - offset

        int offset = 1;
        while(start + offset < len && offset + ret[offset] < length)
        {
            ret[start + offset] = ret[offset];
            ++offset;
        }
        start += offset;
        length -= offset;
    }

    return ret;
}