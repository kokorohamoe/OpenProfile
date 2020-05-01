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
	 * PCMを開く
	 * 引数：
	 * PCMハンドル (snd_pcm_t**)
	 * PCMハンドルの識別子 (const char *)
	 * キャプチャストリーム (snd_pcm_stream_t)
	 * オープンモード
	 *
	 **/

	if((err = snd_pcm_open(&capture_handle, argv[1], SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		fprintf(stderr, "cannot open audio device %s (%s)\n", argv[1], snd_strerror(err));
		exit(1);
	}

	/**
	 * mallocを使ってハードウェアパラメーターのコンフィグレーション領域を確保する
	 */
	fprintf(stdout, "audio interface opened (%s)\n", argv[1]);

	if((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
		fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params allocated\n");

	/**
	 * コンフィグレーション領域を初期化する
	 */
	if((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params initialized\n");

	/**
	 * コンフィグレーション領域に１つのアクセスタイプに設定する
	 * 引数：
	 * PCMハンドル (snd_pcm_t *)
	 * コンフィグレーション領域 (snd_pcm_hw_params *)
	 * アクセスタイプ (snd_pcm_access_t)
	 *
	 * SND_PCM_ACCESS_RW_INTERLEAVED = snd_pcm_readi/snd_pcm_writei access
	 */
	if((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params access type set\n");

	/**
	 * コンフィグレーション領域に１つのサンプリングフォーマットに設定する
	 * 引数
	 * PCMハンドル (snd_pcm_t *)
	 * コンフィグレーション領域 (snd_pcm_hw_params *)
	 * サンプリングフォーマット (snd_pcm_format_t)
	 */
	if((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, format)) < 0) {
		fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params format set\n");

	/**
	 * コンフィグレーション領域にターゲットに近いサンプリングレートに設定する
	 * 引数
	 * PCMハンドル (snd_pcm_t *)
	 * コンフィグレーション領域 (snd_pcm_hw_params *)
	 * 大凡のサンプリングレート (unsigned int *)
	 * サブユニットの方向
	 */
	if((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0) {
		fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params rate set\n");

	/**
	 * コンフィグレーション領域にチャネル数を設定する
	 * 引数
	 * PCMハンドル (snd_pcm_t *)
	 * コンフィグレーション領域 (snd_pcm_hw_params *)
	 * チャネル数 (unsigned int)
	 */
	if((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 2)) < 0) {
		fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params channels set\n");

	/**
	 * コンフィグレーションを設定
	 */
	if((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
		fprintf(stderr, "cannot set hw_params (%s)\n", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "hw_params set\n");

	/**
	 * コンフィグレーション領域の開放
	 */
	snd_pcm_hw_params_free(hw_params);

	fprintf(stdout, "hw_params freed\n");

	/**
	 * オーディオインターフェースの開始
	 */
	if((err = snd_pcm_prepare(capture_handle)) < 0) {
		fprintf(stderr, "cannot prepare audio interface for use (%s)", snd_strerror(err));
		exit(1);
	}

	fprintf(stdout, "audio interface prepared\n");

	/**
	 * キャプチャー用のバッファーを確保
	 */
	buffer = malloc(128 * snd_pcm_format_width(format) / 8 * 2);

	fprintf(stdout, "buffer allocated\n");

	/**
	 * キャプチャー
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
	 * PCMを閉じる
	 */
	snd_pcm_close(capture_handle);

	fprintf(stdout, "audio interface closed\n");


	exit(0);

}