class Solution {
public:
    int missingInteger(vector<int>& nums) {
        
        int sum = nums[0];

        // Find longest sequential prefix
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            }
            else {
                break;
            }
        }

        // Put all elements into a set
        unordered_set<int> s(nums.begin(), nums.end());

        // Find smallest missing integer >= sum
        int x = sum;

        while (s.count(x)) {
            x++;
        }

        return x;
    }
};