class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> freq;

        for (char ch : s)
            freq[ch]++;

        vector<pair<char, int>> v(freq.begin(), freq.end());

        sort(v.begin(), v.end(), [](auto &a, auto &b) {
            return a.second > b.second;
        });

        string ans;

        for (auto &it : v)
            ans.append(it.second, it.first);

        return ans;
    }
};