class Solution {
    public:
    int digitRange(int x) {
        if (x == 0) return 0;

        int mn = 9;
        int mx = 0;

        while (x > 0) {
            int d = x % 10;
            mn = min(mn, d);
            mx = max(mx, d);
            x /= 10;
        }

        return mx - mn;
    }

    int maxDigitRange(vector<int>& nums) {
        int maxRange = -1;
        int sum = 0;

        for (int num : nums) {
            int range = digitRange(num);

            if (range > maxRange) {
                maxRange = range;
                sum = num;
            }
            else if (range == maxRange) {
                sum += num;
            }
        }

        return sum;
    }
};
