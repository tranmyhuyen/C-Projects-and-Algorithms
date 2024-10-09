#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int hour, minute, second;
	hour = minute = second = 0;
	while(1){
		//xóa màn hình console
		//Win cls >< Unix clear
		system("cls");
		//print fomat hh : mm : ss
		printf("%02d : %02d : %02d", hour, minute, second);
		
		fflush(stdout);
		//Lệnh này dùng để xóa bộ nhớ đệm của stdout (luồng xuất dữ liệu)
		// Cập nhật ngay lập tức thời gian mà không phải chờ
		
		//increse second
		second++;
		//update hour, minute, second
		if(second == 60){
			minute += 1;
			second = 0;
		}
		if(minute == 60){
			hour += 1;
			minute = 0;
		}
		if(hour == 24){
			hour = 0;
			minute = 0;
			second = 0;
		}
		sleep(1); 
		//Dừng chương trình trong 1 giây
		// Linus/MacOS sleep(1) >< Win sleep(1000)
	}
	
	return 0;
}