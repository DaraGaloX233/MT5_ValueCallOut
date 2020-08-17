//+------------------------------------------------------------------+
//|                                              EX_time_CONTROL.mq5 |
//|                        Copyright 2020, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- indicator buffers mapping
//---
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime &time[],
                const double &open[],
                const double &high[],
                const double &low[],
                const double &close[],
                const long &tick_volume[],
                const long &volume[],
                const int &spread[])
  {
//---
   static datetime FirstTimeStart=TimeCurrent();
   datetime nowTime=TimeCurrent();//nowtime

   int bar_counter=Bars(_Symbol,_Period,FirstTimeStart,nowTime);
   int Minbar_counter=Bars(_Symbol,PERIOD_M1,FirstTimeStart,nowTime);
   int Hourbar_counter=Bars(_Symbol,PERIOD_H1,FirstTimeStart,nowTime);
   int Daybar_counter=Bars(_Symbol,PERIOD_D1,FirstTimeStart,nowTime);
   int Weekbar_counter=Bars(_Symbol,PERIOD_W1,FirstTimeStart,nowTime);

   double prev_weekClosePrice=iClose(_Symbol,PERIOD_D1,Weekbar_counter);//
   double prev_weekOpenPrice=iOpen(_Symbol,PERIOD_D1,Weekbar_counter);
   double prev_weekHigh=iHigh(_Symbol,PERIOD_D1,Weekbar_counter);
   double prev_weeklOW=iLow(_Symbol,PERIOD_D1,Weekbar_counter);

	int countSec=nowTime%60;//count start from day
	int countMin=nowTime%3600/60;
	int countHour=nowTime%86400/3600;
   int DayStartSec=nowTime%86400;
 	
 	datetime mTimeLocal=TimeLocal();
 	datetime mTimeGMT=TimeGMT();
 	datetime mTimeTradeServer=TimeTradeServer();
 	
 	bool LocalGmtServer=false;
 	if (mTimeLocal==mTimeGMT&&mTimeGMT==mTimeTradeServer&&mTimeLocal==mTimeTradeServer)
 	{
 		LocalGmtServer=true;
 	}
 		else LocalGmtServer=false;

 	//604800s for one week
 	

   string text="prev_weekClosePrice: "+DoubleToString(prev_weekClosePrice) +"\n"+
               "prev_weekOpenPrice: "+DoubleToString(prev_weekOpenPrice) +"\n"+
               "prev_weekHigh: "+DoubleToString(prev_weekHigh) +"\n"+
               "prev_weeklOW: "+DoubleToString(prev_weekClosePrice) +"\n"+
               "DayofWeek: "+IntegerToString(DayofWeek()) +"\n"+
						""+"\n"+
               "bar_counter: "+IntegerToString(bar_counter)+"\n"+
               "Minbar_counter: "+IntegerToString(Minbar_counter)+"\n"+
               "Hourbar_counter: "+IntegerToString(Hourbar_counter)+"\n"+
               "Daybar_counter: "+IntegerToString(Daybar_counter)+"\n"+
               "Weekbar_counter: "+IntegerToString(Weekbar_counter)+"\n"+
               	""+"\n"+
               "nowTime: "+IntegerToString(nowTime)+"\n"+
               "FirstTimeStart: "+IntegerToString(FirstTimeStart)+"\n"+
					"countSec: "+IntegerToString(countSec)+"\n"+
					"countMin: "+IntegerToString(countMin)+"\n"+
					"countHour: "+IntegerToString(countHour)+"\n"+
					"Number of seconds since the day start: "+IntegerToString(DayStartSec)+"\n"+
               "whole code run in: "+TimeToString(nowTime-FirstTimeStart)+"\n"+
						""+"\n"+
					"TimeLocal: "+IntegerToString(mTimeLocal)+"\n"+
					"TimeGMT: "+IntegerToString(mTimeGMT)+"\n"+
					"TimeTradeServer: "+IntegerToString(mTimeTradeServer)+"\n"+
					"Is local time=GMT time=Server Time?: "+IntegerToString(LocalGmtServer);
   Comment(text);
//--- return value of prev_calculated for next call
   return(rates_total);
  }

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int DayofWeek()
  {
   MqlDateTime ntime;
   TimeCurrent(ntime);
   return (ntime.day_of_week);
  }

//+------------------------------------------------------------------+




//+------------------------------------------------------------------+
