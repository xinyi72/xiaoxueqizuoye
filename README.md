# xiaoxueqizuoye


## 项目名称：大奖赛现场统分

需要完成的就是：
某大奖赛有 n 个选手参赛，m（m>2）个评委依次为参赛的选手评判打分，最高10分，最低0分。统分规则为：在每个选手所得的 m 个得分中，去掉一个最高分，去掉一个最低分，取平均分为该选手的最后得分。要求编程实现：
根据 n 个选手的最后得分，从高到低排出名次表，以便确定获奖名单；
根据各选手的最后得分与各评委给该选手所评分的差距，对每个评委评分的准确性给出一个定量的评价。

需要编写排序函数，计算分数的函数，输入的函数和输出的函数，输入输出可以放到main函数但是，放到main函数就会显的非常的乱所以就单独写了一个函数。
因为有时候会手滑打错然后就又声明了一个函数是判断编号有没有重复
bool IsUniqueID(int id, int currentIndex, int ids[], int maxCount);

void InputScores();

void zuihoufenshu();

void SortScores();

void shuchupaiming();
