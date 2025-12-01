#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define Max 100
struct Location{
    char name[50];
    char address[100];
};
struct Passenger{
    char name[50];
    char phone[15];
};
struct Trip{
    char tripId[20];
    struct Location departure;
    struct Location destination;
    char date[20];
    char totalSeats[Max];
    int bookedSeats;
};
struct Ticket{
    char ticketId[20];
    char tripId[20];
    struct Passenger passenger;
    int seatNumber;
    double price;
    int paymentStatus;
    char date[20];
    int status;
};
// Danh sach chuyen xe va ve
struct Trip trips[Max];
int tripCount = 0;
struct Ticket tickets[Max];
int ticketCount = 0;
// Prototype
void printMenu();
void error(char *prompt, char *buffer, int size);
void createNewTrip();
void hienThiTrips();
void updateTripInfo();
void bookTicket();
void checkTicket();
void ticketShow();
int isOnlyNumber(char *s);
int seatIsBooked(char tripId[], int seat);
void listTrips();
void payTicket();
void manageTicket();
void ticketRevenue();
int main(){
	addSampleData();
    int choice;
    do {
        printMenu();
        printf("Nhap lua chon cua ban: ");
        char input[20];
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = 0;
		// Kiem tra rong 
		int onlySpace = 1;
		for(int i = 0; i < strlen(input); i++){
			if(!isspace(input[i])){
				onlySpace = 0;
				break;
			}
		}
		if(strlen(input) == 0 || onlySpace){
		printf("Vui long khong nhap phan tu rong!\n");
		continue;
		}
		if(!isOnlyNumber(input)){
		printf("Ki tu khong duoc nhap! Vui long nhap lai.\n");
		continue;
	}
	choice = atoi(input);
    switch(choice){
	case 1: createNewTrip();break;
	case 2: updateTripInfo();break;
	case 3: bookTicket();break;
	case 4: checkTicket();break;
	case 5: listTrips();break;
	case 6: payTicket();break;
	case 7: manageTicket();break;
	case 8: ticketRevenue();break;
	case 9: printf("Thoat chuong trinh.\n"); break;
	default: printf("Lua chon khong hop le! Vui long nhap lai.\n");break;
}
    } while(choice!=9);
    return 0;
}
void printMenu(){
    printf("+------------------MENU------------------+\n");
    printf("|%-40s|\n","1. Them chuyen xe moi.");
    printf("|%-40s|\n","2. Cap nhap thong tin chuyen xe.");
    printf("|%-40s|\n","3. Dat ve.");
    printf("|%-40s|\n","4. Kiem tra tinh trang ve.");
    printf("|%-40s|\n","5. Liet ke chuyen xe.");
    printf("|%-40s|\n","6. Thanh toan ve.");
    printf("|%-40s|\n","7. Quan ly trang thai ve.");
    printf("|%-40s|\n","8. Bao cao doanh thu va thong ke ve.");
    printf("|%-40s|\n","9. Thoat chuong trinh.");
    printf("+----------------------------------------+\n");
}
int validDate(char *date){
    int d, m, y;
    if(sscanf(date, "%d/%d/%d", &d, &m, &y) != 3) return 0;
    if(m < 1 || m > 12) return 0;
    int md;
    if(m == 2) md = ((y%4==0 && y%100!=0)||(y%400==0)?29:28);
    else if(m==4||m==6||m==9||m==11) md = 30;
    else md = 31;
    if(d < 1 || d > md) return 0;
    return 1;
}
int compareDate(char *d1, char *d2){
    int day1, mon1, year1;
    int day2, mon2, year2;
    sscanf(d1, "%d/%d/%d", &day1, &mon1, &year1);
    sscanf(d2, "%d/%d/%d", &day2, &mon2, &year2);
    if(year1 != year2) return year1 > year2;
    if(mon1 != mon2) return mon1 > mon2;
    return day1 > day2;
}
// Ham nhap khong de trong
void error(char *prompt, char *buffer, int size){
    do{
        printf("%s", prompt);
        fgets(buffer, size, stdin);
        buffer[strcspn(buffer,"\n")]=0;
        if(strlen(buffer)==0)
            printf("Khong duoc de trong! Vui long nhap lai.\n");
    } while(strlen(buffer)==0);
}
// Kiem tra chuoi chi co so
int isOnlyNumber(char *s){
    for(int i=0;i<strlen(s);i++){
        if(s[i]<'0' || s[i]>'9') return 0;
    }
    return 1;
}
// Kiem tra ghe da dat chua
int seatIsBooked(char tripId[], int seat){
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].tripId, tripId)==0 && tickets[i].seatNumber==seat && tickets[i].status != 2)
            return 1;
    }
    return 0;
}
// Them chuyen xe moi
void createNewTrip(){
    if(tripCount>=Max){
        printf("Danh sach chuyen xe da day! Them that bai!\n");return;}
    struct Trip newTrip;
    printf("+------------THEM CHUYEN XE MOI-------------+\n");
    error("Nhap ma chuyen xe: ", newTrip.tripId, 20);
    for(int i=0;i<tripCount;i++){
        if(strcmp(trips[i].tripId,newTrip.tripId)==0){
            printf("Ma chuyen xe da ton tai. Them that bai!\n");
            hienThiTrips();
            return;
        }
    }
    error("Nhap ten diem di: ", newTrip.departure.name,50);
    error("Nhap dia chi diem di: ", newTrip.departure.address,100);
    error("Nhap ten diem den: ", newTrip.destination.name,50);
    error("Nhap dia chi diem den: ", newTrip.destination.address,100);
    do{
        error("Nhap ngay gio chuyen (dd/mm/yyyy): ", newTrip.date, Max);
        if(!validDate(newTrip.date)){
        	printf("Ngay khong hop le!\n");
		}else break;
    }while(1);
    do{
        error("Nhap tong so ghe: ", newTrip.totalSeats, Max);
        if(atoi(newTrip.totalSeats)<=0)
            printf("So ghe phai >0!\n");
    }while(atoi(newTrip.totalSeats)<=0);
    printf("+-------------------------------------------+\n");
    newTrip.bookedSeats=0;
    trips[tripCount++]=newTrip;
    printf("Them chuyen xe thanh cong!\n");
}
// Hien thi danh sach chuyen xe
void hienThiTrips(){
    if(tripCount==0){
        printf("Khong co chuyen xe nao!\n");
        return;
    }
    printf("+------------------------------------DANH SACH CHUYEN XE------------------------------------+\n");
    printf("|%-5s|%-10s|%-15s|%-15s|%-20s|%-10s|%-10s|\n",
           "STT","TripID","Diem Di","Diem Den","Ngay","Tong ghe","Da dat");
    printf("+-------------------------------------------------------------------------------------------+\n");
    for(int i=0;i<tripCount;i++){
        printf("|%-5d|%-10s|%-15s|%-15s|%-20s|%-10s|%-10d|\n",
            i+1,trips[i].tripId,trips[i].departure.name,trips[i].destination.name,trips[i].date,trips[i].totalSeats,trips[i].bookedSeats);
    }
    printf("+-------------------------------------------------------------------------------------------+\n");
}
// Cap nhat thong tin chuyen xe
void updateTripInfo(){
    if(tripCount==0){ printf("Danh sach chuyen xe trong!\n"); return; }
    char tripId[20];
    error("Nhap ma chuyen xe can cap nhat: ", tripId, 20);
    int found=0;
    for(int i=0;i<tripCount;i++){
        if(strcmp(trips[i].tripId,tripId)==0){
            found=1;
            struct Trip *t=&trips[i];
            error("Nhap ten diem di moi: ", t->departure.name,50);
            error("Nhap dia chi diem di moi: ", t->departure.address,100);
            error("Nhap ten diem den moi: ", t->destination.name,50);
            error("Nhap dia chi diem den moi: ", t->destination.address,100);
            do{
                error("Nhap ngay chuyen moi (dd/mm/yyyy): ", t->date, Max);
                if(!validDate(t->date)){
                	printf("Ngay khong hop le!\n");
				}else break;
            }while(1);
            int newSeats;
            do{
                error("Nhap tong so ghe moi: ", t->totalSeats, Max);
                newSeats=atoi(t->totalSeats);
                if(newSeats<t->bookedSeats)
                    printf("So ghe moi phai >= so ghe da dat (%d)!\n", t->bookedSeats);
            }while(newSeats<t->bookedSeats);
            printf("Cap nhat thong tin chuyen xe thanh cong!\n");
            return;
        }
    }
    if(!found){
        printf("Khong tim thay chuyen xe voi ma %s\n", tripId);
        hienThiTrips();
    }
}
// Dat ve
void bookTicket(){
    if(tripCount==0){ printf("Chua co chuyen xe nao!\n"); return; }
    struct Ticket newTicket;
    char seatStr[10];
    error("Nhap ma chuyen xe: ", newTicket.tripId, 20);
    int foundTrip=-1;
    for(int i=0;i<tripCount;i++){
        if(strcmp(trips[i].tripId,newTicket.tripId)==0){
            foundTrip=i; break;
        }
    }
    if(foundTrip==-1){
        printf("Ma chuyen xe khong ton tai!\n"); hienThiTrips(); return;
    }
    struct Trip *t=&trips[foundTrip];
    if(atoi(t->totalSeats) <= t->bookedSeats){
        printf("Chuyen xe da het cho!\n"); return;
    }
    error("Nhap ten hanh khach: ", newTicket.passenger.name, 50);
    do{
        error("Nhap so dien thoai: ", newTicket.passenger.phone, 15);
        if(!isOnlyNumber(newTicket.passenger.phone) || strlen(newTicket.passenger.phone)!=10)
            printf("SDT chi co 10 chu so!\n");
    } while(!isOnlyNumber(newTicket.passenger.phone) || strlen(newTicket.passenger.phone)!=10);
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].passenger.phone,newTicket.passenger.phone)==0 &&
           strcmp(tickets[i].tripId,newTicket.tripId)==0 &&
           tickets[i].status != 2){
            if(strcmp(tickets[i].passenger.name,newTicket.passenger.name)!=0){
                printf("Loi: SDT nay da co nguoi dat!\n");
                return;
            }
        }
    }
    int seat;
    do{
        error("Nhap so ghe: ", seatStr, 10);
        seat = atoi(seatStr);
        if(seat<=0 || seat>atoi(t->totalSeats)) printf("So ghe khong hop le!\n");
        else if(seatIsBooked(newTicket.tripId, seat)) printf("Ghe nay da duoc dat!\n");
        else break;
    }while(1);
    newTicket.seatNumber = seat;
    do{
        error("Nhap ngay dat ve (dd/mm/yyyy): ", newTicket.date, Max);
        if(!validDate(newTicket.date))printf("Ngay khong hop le!\n");
        else if(compareDate(newTicket.date, t->date))
            printf("Ngay dat ve phai nho hon hoac bang ngay chuyen xe!\n");
        else break;
    }while(1);
    newTicket.price = 20000;
    newTicket.paymentStatus = 0;
    newTicket.status = 0;
    // Tao ticketId
    sprintf(newTicket.ticketId,"TICKET%d", ticketCount+1);
    tickets[ticketCount++] = newTicket;
    t->bookedSeats++;
    printf("Dat ve thanh cong! Ma ve cua ban: %s\n", newTicket.ticketId);
}
// Kiem tra tinh trang ve
void checkTicket(){
    if(ticketCount == 0){
        printf("Chua co ve nao!\n");
        return;
    }
    char ticketId[20];
    error("Nhap ma ve can kiem tra: ", ticketId, 20);
    int found = 0;
    for(int i = 0; i < ticketCount; i++){
        if(strcmp(tickets[i].ticketId, ticketId) == 0){
            found = 1;
            printf("+----------- THONG TIN VE -----------+\n");
            printf("|%-15s|%-20s|\n", "Ma ve", tickets[i].ticketId);
            printf("|%-15s|%-20s|\n", "Hanh khach", tickets[i].passenger.name);
            printf("|%-15s|%-20s|\n", "SDT", tickets[i].passenger.phone);
            printf("+----------------+-------------------+\n");
            for(int j = 0; j < tripCount; j++){
                if(strcmp(trips[j].tripId, tickets[i].tripId) == 0){
                    printf("|%-15s|%-20s|\n", "Chuyen xe", trips[j].tripId);
                    printf("|%-15s|%-20s|\n", "Diem di", trips[j].departure.name);
                    printf("|%-15s|%-20s|\n", "Diem den", trips[j].destination.name);
                    printf("|%-15s|%-20s|\n", "Ngay", trips[j].date);
                    printf("+----------------+-------------------+\n");
                    break;
                }
            }
            printf("|%-15s|%-20d|\n", "So ghe", tickets[i].seatNumber);
            printf("|%-15s|%-20.0f|\n", "Gia ve", tickets[i].price);
            printf("|%-15s|%-20s|\n", 
                "Thanh toan", 
                tickets[i].paymentStatus == 1 ? "Da thanh toan" : "Chua thanh toan"
            );
            const char *tt;
            if(tickets[i].status == 1) tt = "Da khoa";
            else if(tickets[i].status == 2) tt = "Da huy";
            else tt = "Chua kich hoat";
            printf("|%-15s|%-20s|\n", "Trang thai", tt);
            printf("+------------------------------------+\n");
            return;
        }
    }
    if(!found){
        printf("Khong tim thay ve voi ma %s!\n", ticketId);
        ticketShow();
    }
}
//hien thi ve hien co 
void ticketShow(){
    printf("+----------------------------DANH SACH VE-----------------------------------+\n");
    printf("|%-10s|%-15s|%-15s|%-16s|%-15s|\n",
           "Ma ve", "Hanh khach", "SDT", "Thanh toan", "Trang thai");
    printf("+---------------------------------------------------------------------------+\n");
    for(int i=0;i<ticketCount;i++){
        const char *pay;
        const char *st;
        pay = tickets[i].paymentStatus ? "Da thanh toan" : "Chua thanh toan";
        if(tickets[i].status == 1) st = "Da khoa";
        else if(tickets[i].status == 2) st = "Da huy";
        else st = "chua thao tac";
        printf("|%-10s|%-15s|%-15s|%-16s|%-15s|\n",
               tickets[i].ticketId,tickets[i].passenger.name,tickets[i].passenger.phone,pay,st
        );
    }
    printf("+---------------------------------------------------------------------------+\n");
}
// liet ke
void listTrips(){
    if(tripCount==0){
        printf("Khong co chuyen xe de hien thi!\n");
        return;
    }
    int pageSize=10;
    char input[20];
    printf("Nhap so dong / trang : ");
    fgets(input, sizeof(input), stdin);
    if(strlen(input) > 1)
        pageSize = atoi(input);
    if(pageSize <= 0){
        printf("pageSize phai > 0!\n");
        return;
    }
    int totalPages = (tripCount + pageSize - 1) / pageSize;
    int pageNumber = 1;
    char choice;
    do{
        int start = (pageNumber - 1) * pageSize;
        int end = start + pageSize;
        if(end > tripCount) end = tripCount;
        printf("+--------------------DANH SACH CHUYEN XE (Trang %d/%d)-------------------------+\n",pageNumber,totalPages);
        printf("|%-5s|%-10s|%-15s|%-15s|%-16s|%-10s|\n",
               "STT","TripID","Diem Di","Diem Den","Ngay","Ghe");
        printf("+-----+----------+---------------+---------------+----------------+----------+\n");
        for(int i=start;i<end;i++){
            printf("|%-5d|%-10s|%-15s|%-15s|%-16s|%-10s|\n",
                i+1,trips[i].tripId,trips[i].departure.name,trips[i].destination.name,trips[i].date,trips[i].totalSeats);
        }
        printf("+----------------------------------------------------------------------------+\n");
        printf("[N] Next | [P] Previous | [X] Search | [Q] Thoat\n");
        printf("Chon: ");
        choice = getchar();
        while(getchar()!='\n');
        if(choice=='N' || choice=='n'){
            if(pageNumber < totalPages) pageNumber++;
        }
        else if(choice=='P' || choice=='p'){
            if(pageNumber > 1) pageNumber--;
        }
        else if(choice=='X' || choice=='x'){ 
            char pageInput[10];
            printf("Nhap so trang (1-%d): ", totalPages);
            fgets(pageInput, sizeof(pageInput), stdin);
            pageInput[strcspn(pageInput,"\n")] = 0;
            if(!isOnlyNumber(pageInput)){
                printf("Nhap khong hop le!\n");
            } else {
                int target = atoi(pageInput);
                if(target >= 1 && target <= totalPages){
                    pageNumber = target;
                } else {
                    printf("So trang phai tu 1 den %d!\n", totalPages);
                }
            }
        }
        else if(choice=='Q' || choice=='q'){
            break;
        }
    }while(1);
}
//thanh toan ticket
void payTicket(){
    if(ticketCount==0){
        printf("Chua co ve nao!\n");
        return;
    }
    char ticketId[20];
    error("Nhap ma ve can thanh toan: ", ticketId, 20);
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].ticketId, ticketId)==0){
            if(tickets[i].status != 0){
                printf("Khong the thanh toan! Trang thai ve: %s\n",
                    tickets[i].status==1?"Da Khoa":"Da Huy");
                return;
            }
            if(tickets[i].paymentStatus==1){
                printf("Ve nay da duoc thanh toan truoc do!\n");
                return;
            }
            tickets[i].paymentStatus = 1;
            printf("Thanh toan ve thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay ve %s!\n", ticketId);
    ticketShow();
}
void manageTicket(){
    if(ticketCount==0){
        printf("Chua co ve nao!\n");
        return;
    }
    char ticketId[20];
    error("Nhap ma ve: ", ticketId, 20);
    int found = 0;
    for(int i=0;i<ticketCount;i++){
        if(strcmp(tickets[i].ticketId, ticketId)==0){
            found = 1;
            if(tickets[i].status != 0){
                printf("Khong the thao tac. Trang thai ve: %s\n",
                    tickets[i].status==1?"Locked":"Canceled");
                return;
            }
            int exit = 0;
            do {
                printf("\n+-----QUAN LY TRANG THAI VE-----+\n");
                printf("|%-31s|\n","1. Khoa ve");
                printf("|%-31s|\n","2. Huy ve");
                printf("|%-31s|\n","3. Thoat");
                printf("+-------------------------------+\n");
                char buf[10];
                printf("Chon: ");
                fgets(buf, sizeof(buf), stdin);
                buf[strcspn(buf, "\n")] = 0;
                if(strlen(buf)==0){
                    printf("Vui long khong nhap rong!\n");
                    continue;
                }
                if(!isOnlyNumber(buf)){
                    printf("Vui long nhap so!\n");
                    continue;
                }
                int ch = atoi(buf);
                if(ch==3){ exit = 1; break; }
                if(ch!=1 && ch!=2){
                    printf("Lua chon khong hop le!\n");
                    continue;
                }
                if(ch==1){ // Khoa ve
                    if(tickets[i].paymentStatus==0){
                        printf("Khong the khoa ve chua thanh toan!\n");
                    } else {
                        tickets[i].status = 1;
                        printf("Khoa ve thanh cong!\n");
                    }
                } else if(ch==2){
                    if(tickets[i].paymentStatus==1){
                        printf("Khong the huy ve da thanh toan!\n");
                    } else {
                        tickets[i].status = 2;
                        // Giai phong ghe
                        for(int j=0;j<tripCount;j++){
                            if(strcmp(trips[j].tripId, tickets[i].tripId)==0){
                                if(trips[j].bookedSeats > 0)
                                    trips[j].bookedSeats--;
                                break;
                            }
                        }
                        printf("Huy ve thanh cong!\n");
                    }
                }
            } while(!exit);
            break;
        }
    }
    if(!found){
        printf("Khong tim thay ve!\n");
        ticketShow();
    }
}
// doanh thu va so lieu 
void ticketRevenue() {
    if(ticketCount == 0){
        printf("Khong co du lieu de bao cao!\n");
        return;
    }
    printf("Chon loai bao cao:\n");
    printf("1 = Tong doanh thu\n");
    printf("2 = Thong ke theo chuyen xe\n");
    printf("3 = Thong ke theo khoang thoi gian\n");
    char buf[10];
    int type;
    do {
        printf("Nhap lua chon (1-3): ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;
        if(!isOnlyNumber(buf)){
            printf("Lua chon khong hop le! Vui long nhap so.\n");
            continue;
        }
        type = atoi(buf);
        if(type < 1 || type > 3){
            printf("Loai bao cao khong hop le!\n");
            continue;
        }
        break;
    } while(1);
    const double pricePerTicket = 20000;
    if(type == 1){
        int validTickets = 0;
        for(int i = 0; i < ticketCount; i++){
            if(tickets[i].status != 2){ // Bao gom ve chua kich hoat va ve da khoa
                validTickets++;
            }
        }
        double revenue = validTickets * pricePerTicket;
        printf("\n--- Bao cao tong doanh thu ---\n");
        printf("Tong doanh thu: %.0f VND\n", revenue);
        printf("Tong ve con hieu luc: %d\n", validTickets);
    }
    else if(type == 2){
        printf("\n--- Thong ke theo chuyen xe ---\n");
        printf("%-10s %-10s %-10s %-5s %-10s\n", 
               "TripID", "Tong ve", "Da TT", "Huy", "Doanh thu"); 
        for(int i = 0; i < tripCount; i++){
            int total = 0, paid = 0, canceled = 0; 
            for(int j = 0; j < ticketCount; j++){
                if(strcmp(tickets[j].tripId, trips[i].tripId) == 0){
                    total++;
                    if(tickets[j].status == 2) canceled++;
                    else if(tickets[j].paymentStatus == 1) paid++;
                }
            }
            double revenue = (total - canceled) * pricePerTicket;
            printf("%-10s %-10d %-10d %-5d %-10.0f\n",
                    trips[i].tripId, total, paid, canceled, revenue);
        }
    }
    else if(type == 3){
        char fromDate[20], toDate[20];
        do{
            error("Nhap ngay bat dau (dd/mm/yyyy): ", fromDate, Max);
            if(!validDate(fromDate)) printf("Ngay khong hop le!\n");
            else break;
        }while(1);
        do{
            error("Nhap ngay ket thuc (dd/mm/yyyy): ", toDate, Max);
            if(!validDate(toDate)) printf("Ngay khong hop le!\n");
            else if(compareDate(fromDate, toDate)) 
                printf("Ngay ket thuc phai lon hon hoac bang ngay bat dau!\n");
            else break;
        }while(1);
        struct Ticket sorted[Max];
        int countSorted = 0;
        for(int i=0;i<ticketCount;i++){
            if(compareDate(fromDate, tickets[i].date)) continue;
            if(compareDate(tickets[i].date, toDate)) continue;
            sorted[countSorted++] = tickets[i];
        }
        for(int i=0;i<countSorted-1;i++){
            for(int j=i+1;j<countSorted;j++){
                if(strcmp(sorted[i].date, sorted[j].date) > 0){
                    struct Ticket tmp = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = tmp;
                }
            }
        }
        char currentDate[20] = "";
        int total=0, canceled=0, valid=0;
        printf("\n--- Bao cao theo khoang thoi gian ---\n");
        printf("%-12s | %-7s | %-10s | %-5s | %-5s\n", "Ngay", "Tong ve", "Doanh thu", "Huy", "Con hieu luc");
        for(int i=0;i<countSorted;i++){
            if(strcmp(currentDate, sorted[i].date) != 0){
                if(strlen(currentDate) > 0){
                    double revenue = valid * pricePerTicket;
                    printf("%-12s | %-7d | %-10.0f | %-5d | %-5d\n",
                           currentDate, total, revenue, canceled, valid);
                }
                strcpy(currentDate, sorted[i].date);
                total = canceled = valid = 0;
            }
            total++;
            if(sorted[i].status == 2) canceled++;
            else valid++;
        }
        if(strlen(currentDate) > 0){
            double revenue = valid * pricePerTicket;
            printf("%-12s | %-7d | %-10.0f | %-5d | %-5d\n",
                   currentDate, total, revenue, canceled, valid);
        }
    }
}
void addSampleData() {
    struct Trip sampleTrips[5] = {
        {"TRIP01", {"Ha Noi", "Noi Bai"}, {"Hai Phong", "Ben xe Hai Phong"}, "01/12/2025", "40", 0},
        {"TRIP02", {"Ha Noi", "Noi Bai"}, {"Nam Dinh", "Ben xe Nam Dinh"}, "02/12/2025", "30", 0},
        {"TRIP03", {"Ha Noi", "Noi Bai"}, {"Hai Duong", "Ben xe Hai Duong"}, "03/12/2025", "25", 0},
        {"TRIP04", {"Ha Noi", "Noi Bai"}, {"Thai Binh", "Ben xe Thai Binh"}, "04/12/2025", "20", 0},
        {"TRIP05", {"Ha Noi", "Noi Bai"}, {"Vinh Phuc", "Ben xe Vinh Phuc"}, "05/12/2025", "35", 0}
    };
    for(int i = 0; i < 5; i++){
        trips[tripCount++] = sampleTrips[i];
    }
    struct Ticket sampleTickets[20] = {
        {"TICKET1","TRIP01",{"Nguyen Van A","0912345670"},1,20000,1,"01/12/2025",0},
        {"TICKET2","TRIP01",{"Tran Thi B","0912345671"},2,20000,1,"01/12/2025",2},
        {"TICKET3","TRIP01",{"Le Van C","0912345672"},3,20000,0,"01/12/2025",2},
        {"TICKET4","TRIP01",{"Pham Thi D","0912345673"},4,20000,1,"01/12/2025",1},
        {"TICKET5","TRIP02",{"Nguyen Van E","0912345674"},1,20000,0,"02/12/2025",0},
        {"TICKET6","TRIP02",{"Tran Thi F","0912345675"},2,20000,1,"02/12/2025",2},
        {"TICKET7","TRIP02",{"Le Van G","0912345676"},3,20000,1,"02/12/2025",0},
        {"TICKET8","TRIP02",{"Pham Thi H","0912345677"},4,20000,0,"02/12/2025",1},
        {"TICKET9","TRIP03",{"Nguyen Van I","0912345678"},1,20000,1,"03/12/2025",1},
        {"TICKET10","TRIP03",{"Tran Thi J","0912345679"},2,20000,0,"03/12/2025",0},
        {"TICKET11","TRIP03",{"Le Van K","0912345680"},3,20000,1,"03/12/2025",2},
        {"TICKET12","TRIP03",{"Pham Thi L","0912345681"},4,20000,1,"03/12/2025",0},
        {"TICKET13","TRIP04",{"Nguyen Van M","0912345682"},1,20000,0,"04/12/2025",1},
        {"TICKET14","TRIP04",{"Tran Thi N","0912345683"},2,20000,1,"04/12/2025",0},
        {"TICKET15","TRIP04",{"Le Van O","0912345684"},3,20000,0,"04/12/2025",0},
        {"TICKET16","TRIP04",{"Pham Thi P","0912345685"},4,20000,1,"04/12/2025",0},
        {"TICKET17","TRIP05",{"Nguyen Van Q","0912345686"},1,20000,1,"05/12/2025",0},
        {"TICKET18","TRIP05",{"Tran Thi R","0912345687"},2,20000,0,"05/12/2025",0},
        {"TICKET19","TRIP05",{"Le Van S","0912345688"},3,20000,1,"05/12/2025",1},
        {"TICKET20","TRIP05",{"Pham Thi T","0912345689"},4,20000,1,"05/12/2025",0}
    };
    for(int i = 0; i < 20; i++){
        tickets[ticketCount++] = sampleTickets[i];
        for(int j = 0; j < tripCount; j++){
            if(strcmp(trips[j].tripId, sampleTickets[i].tripId) == 0)
                trips[j].bookedSeats++;
        }
    }
}
