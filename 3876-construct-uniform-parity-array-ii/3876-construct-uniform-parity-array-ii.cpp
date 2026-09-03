class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // If all elements already have same parity
        bool allEven = true, allOdd = true;

        for (int x : nums1) {
            if (x % 2 != 0)
                allEven = false;
            else
                allOdd = false;
        }

        if (allEven || allOdd)
            return true;

        // Mixed parity is possible only if the smallest
        // element is odd.
        if (mn % 2 == 1)
            return true;

        return false;
    }
};