class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;

        vector<pair<int, int>> litter;

        // Find starting position and litter
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        // Assign an index to every litter cell
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            best[r][c][mask] =
            maximum energy with which we have reached
            (r,c) after collecting 'mask' litter.
        */

        int states = 1 << k;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(
                n,
                vector<int>(states, -1)
            )
        );

        // Queue stores:
        // row, col, mask, remaining energy
        queue<array<int, 4>> q;

        best[sr][sc][0] = energy;

        q.push({sr, sc, 0, energy});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                auto cur = q.front();
                q.pop();

                int r = cur[0];
                int c = cur[1];
                int mask = cur[2];
                int e = cur[3];

                if (mask == fullMask)
                    return moves;

                // If energy is 0, we cannot move.
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    // Collect litter
                    if (id[nr][nc] != -1) {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    /*
                        If we have already reached this
                        state with MORE energy, this new
                        state is useless.
                    */
                    if (best[nr][nc][nmask] >= ne)
                        continue;

                    best[nr][nc][nmask] = ne;

                    q.push({nr, nc, nmask, ne});
                }
            }

            moves++;
        }

        return -1;
    }
};