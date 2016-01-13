navdata_test:
	arm-none-linux-gnueabi-g++ -lpthread -o navdata_test navdata_test5.c gpio_ardrone.c $(CURDIR)/../util/util.c $(CURDIR)/estimate_rincf_drone/estimate_rincf_drone.c $(CURDIR)/quat2rpy/quat2rpy.c $(CURDIR)/rpy2quat/rpy2quat.c $(CURDIR)/rpy2quat/rt_nonfinite.c $(CURDIR)/rpy2quat/rtGetNaN.c $(CURDIR)/rpy2quat/rtGetInf.c $(CURDIR)/transform_mag/transform_mag.c

mag_bias_est:
	arm-none-linux-gnueabi-g++ -lpthread -o mag_bias_est mag_bias_est.c gpio_ardrone.c $(CURDIR)/../util/util.c $(CURDIR)/estimate_rincf_drone/estimate_rincf_drone.c $(CURDIR)/quat2rpy/quat2rpy.c $(CURDIR)/rpy2quat/rpy2quat.c $(CURDIR)/rpy2quat/rt_nonfinite.c $(CURDIR)/rpy2quat/rtGetNaN.c $(CURDIR)/rpy2quat/rtGetInf.c $(CURDIR)/transform_mag/transform_mag.c
