struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};
unordered_map<pair<int,int>,int,HASH>mp;//关于pii的哈希。unodered_map/set只能编码一个关键字，结构体就得自己写了。
