Header header

float32 tm #timestamp
float32 tm_pre
float32 frame

#pitch estimates in radians, positive is pitch down (fly forward)
float32 pitch_w  #=sum(gx * dt)
float32 pitch_a  #=pitch(az,ax)
float32 pitch    #kalman pitch estimate from gy and pitch_a

#roll estimates in radians, positive is roll right (fly rightward)
float32 roll_w    #=sum(gy * dt)
float32 roll_a    #=roll(az,ay)
float32 roll      #kalman roll estimate from gx and roll_a
  
#yaw estimate, positive is yaw left
float32 yaw_w      #=sum(gz * dt)
float32 yaw_m      #=sum(gz * dt)
float32 yaw        #=sum(gz * dt)
  
float64 dt    #time since last navdata sample in sec
float64 dt2
  
float64[4] q_est
float64[3] b_est

#copy of physical navdata values
float64 ts    # navdata timestamp in sec
float32 hraw   # height above ground in [cm] 
float32 h_meas  # 1=height was measured in this sample, 0=height is copy of prev value
float32 ax    # acceleration x-axis in [G] front facing up is positive         
float32 ay    # acceleration y-axis in [G] left facing up is positive                
float32 az    # acceleration z-axis in [G] top facing up is positive  
           
float32 wx    # gyro value x-axis in [rad/sec] right turn, i.e. roll right is positive           
float32 wy    # gyro value y-axis in [rad/sec] right turn, i.e. pirch down is positive                     
float32 wz    # gyro value z-axis in [rad/sec] right turn, i.e. yaw left is positive

float32 magX
float32 magY 
float32 magZ

float32 pressure
float32 rotX
float32 rotY
float32 rotZ

float32 altd

float32 motor1
float32 motor2
float32 motor3
float32 motor4


