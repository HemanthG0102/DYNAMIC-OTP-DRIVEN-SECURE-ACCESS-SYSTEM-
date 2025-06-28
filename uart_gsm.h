//uart_gsm.h

//GSM
#define GSM_RESP_TIMEOUT_MS 5000

int wait_for_response(const char* expected, unsigned int timeout_ms);
int uart_gsm(char *number, char *msg);
