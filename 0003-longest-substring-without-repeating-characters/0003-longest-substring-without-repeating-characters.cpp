class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        unordered_map<char, int> lastPos;

        int left = 0;
        int ans = 0;

        for (int right = 0; right < s.size(); right++) {

            if (lastPos.count(s[right]) &&
                lastPos[s[right]] >= left) {

                left = lastPos[s[right]] + 1;
            }

            lastPos[s[right]] = right;

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};