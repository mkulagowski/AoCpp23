import day;
import std;

int main(int argc, char* argv[])
{
    for (int n = 1; n <= 25; n++) {
        auto day = get_day(n);
        if (day) {
            day->solve();
        } else {
            break;
        }
    }
    
	return 0;
}