#ifndef __RPM_CONTROLLER_H__
  #define __RPM_CONTROLLER_H__

  class rpm_controller{
    private:
      float _kp, _ki, _kd;
      uint8_t _pwm = 0;
      uint16_t _sample_t = 10; // by default we only sample every 10ms
      uint16_t _last_sample = millis();
      
    public:

      rpm_controller(float kp, float ki, float kd, uint16_t sample_t){
        this->_kp = kp;
        this->_ki = ki;
        this->_kd = kd;
        this->_sample_t = sample_t;
      }

      void step(int16_t target_pwm){
        static int16_t prev_pwm, prev_err_i, prev_err_d;

        int16_t err_p, err_i, err_d, dt;

        // Too early to sample again
        uint32_t time_now = millis();
        if(time_now - this->_last_sample < this->_sample_t){
          return;
        }

        dt = time_now - this->_last_sample;
        
        err_p = target_pwm - prev_pwm;
        err_i = prev_err_i + err_p * dt;
        err_d = (err_p - prev_err_d) / dt;
        
        prev_err_i = err_i;
        prev_err_d = err_d;
        
        this->_pwm = (int16_t)(this->_kp*err_p + this->_ki*err_i + this->_kd*err_d);
        
        // constrain the pwm to be in range
        if(this->_pwm < -255 || this->_pwm > 255){
          this->_pwm = (this->_pwm/abs(this->_pwm))*255;
        }

        prev_pwm = this->_pwm;
      }

      uint8_t get_pwm(){
        return this->_pwm;
      }
  };
  
#endif // __RPM_CONTROLLER_H__
