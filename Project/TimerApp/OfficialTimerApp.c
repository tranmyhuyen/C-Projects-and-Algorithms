#include <stdio.h>
#include <stdlib.h> // Để sử dụng system() và các hàm khác
#include <unistd.h> // Để sử dụng sleep() trên Unix/Linux

#ifdef _WIN32
	#include <windows.h> // Để sử dụng Sleep() trên Windows
	#define CLEAR "cls"
	#define SLEEP(x) Sleep(1000 * (x)) // Chuyển đổi giây thành mili giây
#else
	#define CLEAR "clear"
	#define SLEEP(x) sleep(x) // Chuyển đổi giây thành mili giây
#endif

int main(){
	int hour, minute, second;
	hour = minute = second = 0;
	
	while(1){
		// Xóa màn hình console
		system(CLEAR);
		
		// In ra định dạng hh : mm : ss
		printf("%02d : %02d : %02d\n", hour, minute, second);
		fflush(stdout); //// Đảm bảo in ngay lập tức
		
		// Tăng giây
	        second++;
	        
	        // Cập nhật giờ, phút, giây
	        if (second == 60) {
	            minute++;
	            second = 0;
	        }
	        if (minute == 60) {
	            hour++;
	            minute = 0;
	        }
	        if (hour == 24) {
	            hour = 0;
	            minute = 0;
	            second = 0;
        	}
		
		// Chờ 1 giây
	        SLEEP(1);
	}
	return 0;
}
