#ifndef _CombGen_
#define _CombGen_

// Microsoft doesn't include min() template so I had to define it
// Remove it if your compiler will compile without it.
//template<class T>
//const T& min(const T& x, const T& y) { return x < y?x:y; }

// Class to generate combinations given a vector<T>
// The total elements is the size of the passed in vector,
// The number of items to choose is nItems.
template <class T>
        class CombinationGenerator {
public:
    CombinationGenerator(const vector<T>& ElVector, // Original items
                         int nItems=-1) :    // Number of items to choose
    m_Elements(ElVector), m_bNext(true) {
        int nSize = ElVector.size();
        if (nSize > 0) {
            // If no argument given, choose all items
            if (nItems <= 0)
                m_nItems = nSize;
            else
                m_nItems = min(nItems, nSize);
            
            // Bit vector that controls permutations
            m_Bits.resize(nSize, false);
            
            // Initialize nItem bits in vector to "true"
            int i, j;
            for(i=0, j=nSize-1; i<m_nItems; i++, j--) {
                m_Bits[j] = true;
            }
        }
        else
            m_bNext = false; // size is 0, so no combinations are possible
    }
    
    // Get a combination and output results in the passed in vector Output
    bool NextCombination(vector<T>& Output) {
        
        // Erase all elements in output vector
        Output.erase(Output.begin(), Output.end());
        
        // If no more combinations, quit
        if (!m_bNext)
            return false;
        
        if (m_bNext) {
            int nFound = 1;
            // copy only elements that have a "1" in the
            // Bit vector
            int nSize = m_Elements.size();
            for (int j=0; j<nSize && nFound <= m_nItems; j++) {
                if (m_Bits[j] == true) {
                    Output.push_back(m_Elements[j]);
                    nFound++;
                }
            }
            // Get next permutation of bits
            m_bNext = next_permutation(m_Bits.begin(), m_Bits.end());
        }
        // Combination was generated
        return true;
    }
    
private:
    vector<T> m_Elements;
    vector<bool> m_Bits;
    int m_nItems;
    bool m_bNext;
};
#endif
