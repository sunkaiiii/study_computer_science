# 可以直接创建bytes和str对象
print(bytes("Hællå, wørld!", encoding="utf-8"))
print(str(b'H\xc3\xa6ll\xc3\xa5, w\xc3\xb8rld!', encoding="utf-8"))