#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

snd_pcm_hw_params_t *hw_params =NULL;
	
int setStereo()|

	if((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0) {
		printf("Set line in to stereo error\r\n");
		exit(1);
	}
	
	return 0;

}

int main(int argc, char *argv[]) {
	
	initParam();
	setStereo();
	
	
	return 0;

}
