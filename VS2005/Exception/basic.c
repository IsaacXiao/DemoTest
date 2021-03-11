#include  "stdio.h "

void  test()
{
	int *  p  =   0x00000000 ;  //  pointer to NULL

	__try
	{
		puts( " in try " );
		__try
		{
			puts( " in try " );

			//  causes an access violation exception;
			//  导致一个存储异常
			* p  =   13 ; 

			//  呵呵，注意这条语句
			puts( " 这里不会被执行到 " );
		}
		__finally
		{
			puts( " in finally " );
		}

		//  呵呵，注意这条语句
		puts( " 这里也不会被执行到 " );
	}
	__except(puts( " in filter 1 " ),  0 )
	{
		puts( " in except 1 " );
	}
}

void  main1()
{
	puts( " hello " );
	__try
	{
		test();
	}
	__except(puts( " in filter 2 " ),  1 )
	{
		puts( " in except 2 " );
	}
	puts( " world " );
} 