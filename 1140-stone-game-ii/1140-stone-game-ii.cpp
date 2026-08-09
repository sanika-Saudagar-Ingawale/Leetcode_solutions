class Solution {
public:

    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M, vector<int>& piles) {

        // If we can take all remaining piles
        if (i + 2 * M >= n) {
            return suffix[i];
        }

        // Already calculated
        if (dp[i][M] != -1) {
            return dp[i][M];
        }

        int best = 0;

        // Try taking X piles
        for (int X = 1; X <= 2 * M; X++) {

            int opponent = solve(
                i + X,
                max(M, X),
                piles
            );

            int current = suffix[i] - opponent;

            best = max(best, current);
        }

        return dp[i][M] = best;
    }

    int stoneGameII(vector<int>& piles) {

        n = piles.size();

        suffix.resize(n);

        suffix[n - 1] = piles[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = piles[i] + suffix[i + 1];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1, piles);
    }
};