regex tmp(string + '$');
//寻找以string结尾的字符串并以str替换结尾
if (regex_search(x, tmp)) {
    x = regex_replace(x, tmp, str);
}
