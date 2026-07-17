class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> f(mx + 1), cnt(mx + 1);
        for (int x : nums) f[x]++;

        for (int i = 1; i <= mx; i++)
            for (int j = i; j <= mx; j += i)
                cnt[i] += f[j];

        vector<long long> pairs(mx + 1);

        for (int i = mx; i >= 1; i--) {
            pairs[i] = 1LL * cnt[i] * (cnt[i] - 1) / 2;
            for (int j = i * 2; j <= mx; j += i)
                pairs[i] -= pairs[j];
        }

        for (int i = 1; i <= mx; i++)
            pairs[i] += pairs[i - 1];

        vector<int> ans;
        for (long long q : queries)
            ans.push_back(lower_bound(pairs.begin() + 1, pairs.end(), q + 1) - pairs.begin());

        return ans;
    }
};