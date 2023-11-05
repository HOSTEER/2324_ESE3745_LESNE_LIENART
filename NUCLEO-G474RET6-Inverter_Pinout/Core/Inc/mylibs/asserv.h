
typedef struct {
	float Ki, Kp, Kd;
	float target_current;
}h_asserv_t;

extern h_asserv_t asserv_speed;
extern h_asserv_t asserv_current;

int pid_asserv(void);
int asserv_current_init(void);
int asserv_speed_init(void);
void asserv_function_handler(void);
