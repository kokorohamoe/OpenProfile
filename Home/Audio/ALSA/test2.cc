#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

void main(int argc, char *argv[]) {
	//https://gist.github.com/kazz12211/ba3989e74fd76231046c1a5d95651b5e

	int i;
	int err;
	char *buffer;
	int buffer_frames = 128;
	unsigned int rate = 44100;
	snd_pcm_t *capture_handle;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE; // Signed 16 bit Little Endian

	/**
	 * PCM���J��
	 * �����F
	 * PCM�n���h�� (snd_pcm_t**)
	 * PCM�n���h���̎��ʎq (const char *)
	 * �L���v�`���X�g���[�� (snd_pcm_stream_t)
	 * �I�[�v�����[�h
	 *
	 **/

	if((err = snd_pcm_open(&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		fprintf(stderr, "cannot open audio device %s (%s)\n", argv[1], snd_strerror(err));
		exit(1);
	}

	/**
	 * malloc���g���ăn�[�h�E�F�A�p�����[�^�[�̃R���t�B�O���[�V�����̈���m�ۂ���
	 */
	fprintf(stdout, "audio interface opened (%s)\n", argv[1]);

	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
		fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params allocated\n");

	/**
	 * �R���t�B�O���[�V�����̈������������
	 */
	if((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params initialized\n");

	/**
	 * �R���t�B�O���[�V�����̈�ɂP�̃A�N�Z�X�^�C�v�ɐݒ肷��
	 * �����F
	 * PCM�n���h�� (snd_pcm_t *)
	 * �R���t�B�O���[�V�����̈� (snd_pcm_hw_params *)
	 * �A�N�Z�X�^�C�v (snd_pcm_access_t)
	 *
	 * SND_PCM_ACCESS_RW_INTERLEAVED = snd_pcm_readi/snd_pcm_writei access
	 */
	if((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params access type set\n");

	/**
	 * �R���t�B�O���[�V�����̈�ɂP�̃T���v�����O�t�H�[�}�b�g�ɐݒ肷��
	 * ����
	 * PCM�n���h�� (snd_pcm_t *)
	 * �R���t�B�O���[�V�����̈� (snd_pcm_hw_params *)
	 * �T���v�����O�t�H�[�}�b�g (snd_pcm_format_t)
	 */
	if((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, format)) < 0) {
		fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params format set\n");

	/**
	 * �R���t�B�O���[�V�����̈�Ƀ^�[�Q�b�g�ɋ߂��T���v�����O���[�g�ɐݒ肷��
	 * ����
	 * PCM�n���h�� (snd_pcm_t *)
	 * �R���t�B�O���[�V�����̈� (snd_pcm_hw_params *)
	 * ��}�̃T���v�����O���[�g (unsigned int *)
	 * �T�u���j�b�g�̕���
	 */
	if((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0) {
		fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params rate set\n");

	/**
	 * �R���t�B�O���[�V�����̈�Ƀ`���l������ݒ肷��
	 * ����
	 * PCM�n���h�� (snd_pcm_t *)
	 * �R���t�B�O���[�V�����̈� (snd_pcm_hw_params *)
	 * �`���l���� (unsigned int)
	 */
	if((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0) {
		fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params channels set\n");

	/**
	 * �R���t�B�O���[�V������ݒ�
	 */
	if((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot set hw_params (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params set\n");

	/**
	 * �R���t�B�O���[�V�����̈�̊J��
	 */
	snd_pcm_hw_params_free(hw_params);

	fprintf(stdout, "hw_params freed\n");

	/**
	 * �I�[�f�B�I�C���^�[�t�F�[�X�̊J�n
	 */
	if((err = snd_pcm_prepare(capture_handle)) < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "audio interface prepared\n");

	/**
	 * �L���v�`���[�p�̃o�b�t�@�[���m��
	 */
	buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

	fprintf(stdout, "buffer allocated\n");

	/**
	 * �L���v�`���[
	 */
	for(i = 0; i < 10; i++) {
		if((err = snd_pcm_readi(capture_handle, buffer, buffer_frames)) != buffer_frames) {
			fprintf(stderr, "read from audio interface failed (%s)\n", snd_strerror(err));
			exit(1);
		}
		fprintf(stdout, "read %d done\n", i);
	}

	free(buffer);

	fprintf(stdout, "buffer freed\n");

	/**
	 * PCM�����
	 */
	snd_pcm_close(capture_handle);

	fprintf(stdout, "audio interface closed\n");


	exit(0);

}