#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

struct Group {
    int start;
    int length;
};

class SparseTable {
public:
    SparseTable(const vector<int>& nums) : n(nums.size()) {
        if (n == 0) return;
        int maxLog = 32 - __builtin_clz(n);
        st.assign(maxLog, vector<int>(n));
        for (int j = 0; j < n; ++j) {
            st[0][j] = nums[j];
        }
        for (int i = 1; i < maxLog; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) return 0;
        int log = 31 - __builtin_clz(r - l + 1);
        return max(st[log][l], st[log][r - (1 << log) + 1]);
    }

private:
    int n;
    vector<vector<int>> st;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        
        pair<vector<Group>, vector<int>> zeroInfo = getZeroGroups(s);
        vector<Group>& zeroGroups = zeroInfo.first;
        vector<int>& zeroGroupIndex = zeroInfo.second;
        
        int totalZeroGroups = zeroGroups.size();
        vector<int> adjacentSum(max(0, totalZeroGroups - 1));
        for (int i = 0; i < totalZeroGroups - 1; ++i) {
            adjacentSum[i] = zeroGroups[i].length + zeroGroups[i + 1].length;
        }
        
        SparseTable st(adjacentSum);
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            
            int activeSections = totalOnes;
            
            int leftGroupIdx = zeroGroupIndex[l];
            int rightGroupIdx = zeroGroupIndex[r];
            
            int leftLen = (leftGroupIdx == -1) ? 0 : (zeroGroups[leftGroupIdx].start + zeroGroups[leftGroupIdx].length - l);
            int rightLen = (rightGroupIdx == -1) ? 0 : (r - zeroGroups[rightGroupIdx].start + 1);
            
            if (s[l] == '0' && s[r] == '0' && leftGroupIdx + 1 == rightGroupIdx) {
                activeSections = max(activeSections, totalOnes + leftLen + rightLen);
            } else {
                int startAdj = leftGroupIdx + 1;
                int endAdj = (s[r] == '1' ? rightGroupIdx : rightGroupIdx - 1) - 1;
                
                if (startAdj <= endAdj) {
                    activeSections = max(activeSections, totalOnes + st.query(startAdj, endAdj));
                }
            }
            
            if (s[l] == '0' && leftGroupIdx + 1 <= (s[r] == '1' ? rightGroupIdx : rightGroupIdx - 1)) {
                activeSections = max(activeSections, totalOnes + leftLen + zeroGroups[leftGroupIdx + 1].length);
            }
            
            if (s[r] == '0' && leftGroupIdx < rightGroupIdx - 1) {
                activeSections = max(activeSections, totalOnes + rightLen + zeroGroups[rightGroupIdx - 1].length);
            }
            
            ans.push_back(activeSections);
        }
        
        return ans;
    }

private:
    pair<vector<Group>, vector<int>> getZeroGroups(const string& s) {
        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex(s.length());
        
        for (int i = 0; i < (int)s.length(); ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, 1});
                }
            }
            zeroGroupIndex[i] = zeroGroups.empty() ? -1 : (int)zeroGroups.size() - 1;
        }
        
        return {zeroGroups, zeroGroupIndex};
    }
};