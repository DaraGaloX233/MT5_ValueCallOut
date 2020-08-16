//MT5 Time control
//http://blog.sina.com.cn/s/blog_e6fc34b40102wgq4.html
//https://www.mql5.com/zh/articles/599
//https://www.mql5.com/zh/articles/3395

变量储存为 datetime
需要用(string)，TimeToString(tm);换成字符串
StringToTime() 换成数字

ENUM_DAY_OF_WEEK//	sunday to saturday
TimeToString()
转变值包括从01.01.1970起已消耗的秒数，以字符串格式"yyyy.mm.dd hh:mi"

TimeCurrent();//服务器时间
TimeLocal();//本地时间

只要时间以数字形式呈现，各种相关操作就都变得简单方便了
在当前时间的基础上减去或加上一个小时（3600 秒），就会得到一个小时之前或之后的时间：
TimeCurrent()+3600//目前时间一小时后。3600秒
或者static TimeCurrent()再加减秒数就能固定那个小时


datetime    tm=TimeCurrent();
MqlDateTime stm;
TimeToStruct(tm,stm);
//--- output date components
Alert("Year: "        +(string)stm.year);
Alert("Month: "      +(string)stm.mon);
Alert("Day: "      +(string)stm.day);
Alert("Hour: "        +(string)stm.hour);
Alert("Minute: "     +(string)stm.min);
Alert("Second: "    +(string)stm.sec);
Alert("Day of the week: "+(string)stm.day_of_week);
Alert("Day of the year: "  +(string)stm.day_of_year);


确定自日开始起流逝的秒数，只需取时间除以 86400 的余数
datetime tm=TimeCurrent();
long seconds=tm%86400;
//--- output result
Alert("Time elapsed since the day start: "+(string)seconds+" sec.");

TimeFromDayStart(datetime aTime,int &aH,int &aM,int &aS)
aH=(int)((aTime%86400)/3600); hour
aM=(int)((aTime%3600)/60);  minute
aS=(int)(aTime%60); seconds


确定自日开始起流逝的秒数，一天86400秒
bool NewDay=(time[i]/86400)!=(time[i-1]/86400);

确定时段
当天的指定时间范围内、每天按相同的间隔进行交易
1.计算自日开始起的秒数时间，作为时间起始点；同样再算出时间结束点。
2.计算自日开始起以秒计的当前时间。
3.将当前时间与起始、结束时间进行对比
bool TimeSession(int aStartHour,int aStartMinute,int aStopHour,int aStopMinute,datetime aTimeCur)
  {
//--- session start time
   int StartTime=3600*aStartHour+60*aStartMinute;
//--- session end time
   int StopTime=3600*aStopHour+60*aStopMinute;
//--- current time in seconds since the day start
   aTimeCur=aTimeCur%86400;
   if(StopTime<StartTime)
     {
      //--- going past midnight
      if(aTimeCur>=StartTime || aTimeCur<StopTime)
        {
         return(true);
        }
     }
   else
     {
      //--- within one day
      if(aTimeCur>=StartTime && aTimeCur<StopTime)
        {
         return(true);
        }
     }
   return(false);
  }

确定日内的一个时间点
简单地检查与指定时间的相等性不会有效，因为价格变动并不会定期出现，而且可能会有几秒到几分钟的延迟。在指定的时间内，很可能市场中根本就没有任何价格变动。我们需要检查给定的时间戳有无交叉。
bool TimeCross(int aHour,int aMinute,datetime aTimeCur,datetime aTimePre)
  {
//--- specified time since the day start
   datetime PointTime=aHour*3600+aMinute*60;
//--- current time since the day start
   aTimeCur=aTimeCur%86400;
//--- previous time since the day start
   aTimePre=aTimePre%86400;
   if(aTimeCur<aTimePre)
     {
      //--- going past midnight
      if(aTimeCur>=PointTime || aTimePre<PointTime)
        {
         return(true);
        }
     }
   else
     {
      if(aTimeCur>=PointTime && aTimePre<PointTime)
        {
         return(true);
        }
     }
   return(false);
  }
  
  确定一周的交易天数
  input bool Sunday   =true; // Sunday
input bool Monday   =true; // Monday
input bool Tuesday  =true; // Tuesday 
input bool Wednesday=true; // Wednesday
input bool Thursday =true; // Thursday
input bool Friday   =true; // Friday
input bool Saturday =true; // Saturday

bool WeekDays[7];
void WeekDays_Init()
  {
   WeekDays[0]=Sunday;
   WeekDays[1]=Monday;
   WeekDays[2]=Tuesday;
   WeekDays[3]=Wednesday;
   WeekDays[4]=Thursday;
   WeekDays[5]=Friday;
   WeekDays[6]=Saturday;
  }
  bool WeekDays_Check(datetime aTime)
  {
   MqlDateTime stm;
   TimeToStruct(aTime,stm);
   return(WeekDays[stm.day_of_week]);
  }
  
  确定月内天数的函数
  int DaysInMonth(datetime aTime)
  {
   MqlDateTime stm;
   TimeToStruct(aTime,stm);
   if(stm.mon==2)
     {
      //--- February
      if(LeapYear(aTime))
        {
         //--- February in a leap year 
         return(29);
        }
      else
        {
         //--- February in a non-leap year 
         return(28);
        }
     }
   else
     {
      //--- other months
      return(31-((stm.mon-1)%7)%2);
     }
  }