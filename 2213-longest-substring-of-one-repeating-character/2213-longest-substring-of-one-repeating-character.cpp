class Solution {
public:
    struct Node {
        char leftChar, rightChar;
        int prefix, suffix, best, len;

        Node() {
            leftChar = rightChar = '#';
            prefix = suffix = best = len = 0;
        }
    };

    vector<Node> seg;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.prefix = a.prefix;
        res.suffix = b.suffix;

        // If the whole left part has one character
        // and it matches the first character of right part
        if (a.leftChar == b.leftChar && a.prefix == a.len) {
            res.prefix = a.len + b.prefix;
        }

        // If the whole right part has one character
        // and it matches the last character of left part
        if (a.rightChar == b.rightChar && b.suffix == b.len) {
            res.suffix = b.len + a.suffix;
        }

        res.best = max(a.best, b.best);

        // Join suffix of left + prefix of right
        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.suffix + b.prefix);
        }

        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            seg[idx].leftChar = s[l];
            seg[idx].rightChar = s[l];
            seg[idx].prefix = 1;
            seg[idx].suffix = 1;
            seg[idx].best = 1;
            seg[idx].len = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);

        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

    void update(int idx, int l, int r, int pos, char ch) {
        if (l == r) {
            seg[idx].leftChar = ch;
            seg[idx].rightChar = ch;
            seg[idx].prefix = 1;
            seg[idx].suffix = 1;
            seg[idx].best = 1;
            seg[idx].len = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(2 * idx, l, mid, pos, ch);
        else
            update(2 * idx + 1, mid + 1, r, pos, ch);

        seg[idx] = merge(seg[2 * idx], seg[2 * idx + 1]);
    }

    vector<int> longestRepeating(string s,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {

        this->s = s;

        int n = s.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {

            int pos = queryIndices[i];
            char ch = queryCharacters[i];

            s[pos] = ch;

            update(1, 0, n - 1, pos, ch);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};