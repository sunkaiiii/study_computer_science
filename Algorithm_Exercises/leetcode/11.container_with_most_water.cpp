class Solution {
public:
    int maxArea(vector<int>& height) {
        int l=0;
        int r=height.size()-1;
        int result=-1;
        while(l!=r)
        {
            int temp=std::min(height[l],height[r])*(r-l);
            if(temp>result)
            {
                result=temp;
            }
            if(height[l]<height[r])
            {
                l++;
            }else
            {
                r--;
            }
        }
        return result;
    }
};