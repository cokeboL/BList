BList(Binary Search List)
此数据结构由一个双向链表 + 一个数组组成


1.插入
链表在新增元素的过程中保持有序
数组中保存关键节点，比如step为8，随机顺序向链表中插入0-9这10个元素，插入第一个元素时生成一个KeyNode保存在
数组中，这个KeyNode指向链表中第一个元素（head），之后链表中每插入一个新元素，KeyNode中计数+1，当计数超过
step时，也就是插入第9个元素时生成第2个KeyNode（指向链表第9个元素），以此类推，KeyNode一次append到数组尾部

2.查找
通过key删除时，先通过数组中的KeyNode做二分查找，定位到一个KeyNode的key刚好满足小于这个key并且下一个KeyNode
为空或者key大于这个要删除的key，如果找不到满足条件的KeyNode，返回。如果找到，在循环取链表的next来查找，直到
得到key或者key大于此key时为查找失败。

3.删除
先进行查找操作，再调此整节的pre和next节点的pre和next指向，再把此节点所属的KeyNode计数减一并检查是否需要删除
此KeyNode，如需删除，再把此KeyNode后面的KeyNode进行向前一格的memmove操作

4.修改
见插入操作

5.优化
插入和删除可能导致的更新KeyNode的情况，把临界点设置为step/2，比如step=8，当KeyNode所属节点大于step*1.5=12时
才新建KeyNode；删除操作时，当KeyNode所属节点数小于step*0.5=4时就删除此KeyNode，以免极端情况时出现每个KeyNode
对应一个链表节点的情况
