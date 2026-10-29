#include <stdio.h>
#include <math.h>

/* Sampling configuration */
#define FS 16000
#define N 1600
#define PI 3.14159265358979323846f

/* Array to store generated audio samples */
float samples[N];

/* Signal features */
typedef struct
{
    float rms;
    float peak;
    float crest;
    float zcr;
} Features;

/* Reproducible pseudo-random noise generator */
unsigned long noise_state = 12345UL;

float pseudo_noise(void)
{
    noise_state =
        (1103515245UL * noise_state + 12345UL)
        & 0x7FFFFFFFUL;

    return ((float)(noise_state % 20001UL) / 10000.0f)
           - 1.0f;
}

/* --------------------------------------------------
   1. GENERATE SYNTHETIC CLAP-LIKE SIGNAL
   -------------------------------------------------- */
void generate_clap(void)
{
    int i;
    float t;

    for (i = 0; i < N; i++)
    {
        t = (float)i / FS;

        if (t <= 0.035f)
        {
            samples[i] =
                0.95f * expf(-130.0f * t) *
                (0.65f * sinf(2.0f * PI * 1700.0f * t)
                + 0.35f * sinf(2.0f * PI * 3100.0f * t));
        }
        else
        {
            samples[i] = 0.0f;
        }
    }
}

/* --------------------------------------------------
   2. GENERATE SYNTHETIC WHISTLE-LIKE SIGNAL
   -------------------------------------------------- */

void generate_whistle(void)
{
    int i;
    float t;

    for (i = 0; i < N; i++)
    {
        t = (float)i / FS;

        samples[i] =
            0.55f * sinf(2.0f * PI * 2200.0f * t);
    }
}

/* --------------------------------------------------
   3. GENERATE SYNTHETIC BACKGROUND NOISE
   -------------------------------------------------- */

void generate_background(void)
{
    int i;

    for (i = 0; i < N; i++)
    {
        samples[i] = 0.035f * pseudo_noise();
    }
}

/* --------------------------------------------------
   4. EXTRACT SIGNAL FEATURES
   -------------------------------------------------- */

Features extract_features(void)
{
    int i;
    int crossings = 0;

    float sum_squares = 0.0f;
    float peak = 0.0f;
    float value;

    Features f;

    for (i = 0; i < N; i++)
    {
        value = samples[i];

        /* Calculate energy */
        sum_squares += value * value;

        /* Calculate peak amplitude */
        if (fabsf(value) > peak)
        {
            peak = fabsf(value);
        }

        /* Count zero crossings */
        if (i > 0)
        {
            if ((samples[i] >= 0.0f &&
                 samples[i - 1] < 0.0f) ||
                (samples[i] < 0.0f &&
                 samples[i - 1] >= 0.0f))
            {
                crossings++;
            }
        }
    }

    /* Root Mean Square amplitude */
    f.rms = sqrtf(sum_squares / N);

    /* Maximum absolute amplitude */
    f.peak = peak;

    /* Crest factor */
    if (f.rms > 0.000001f)
    {
        f.crest = f.peak / f.rms;
    }
    else
    {
        f.crest = 0.0f;
    }

    /* Zero-crossing rate */
    f.zcr = (float)crossings / (N - 1);

    return f;
}

/* --------------------------------------------------
   5. CLASSIFY THE GENERATED SIGNAL
   -------------------------------------------------- */

const char *classify_signal(Features f)
{
    /* Short, high-amplitude transient */
    if (f.peak > 0.45f && f.crest > 4.0f)
    {
        return "CLAP-LIKE";
    }

    /* Strong, relatively steady, high-frequency tone */
    if (f.rms > 0.15f &&
        f.crest < 2.0f &&
        f.zcr > 0.15f)
    {
        return "WHISTLE-LIKE";
    }

    /* Remaining signal pattern */
    return "BACKGROUND-LIKE";
}

/* --------------------------------------------------
   6. PRINT RESULTS TO CCS CIO CONSOLE
   -------------------------------------------------- */

void run_test(const char *name)
{
    Features f;

    f = extract_features();

    printf("\n");
    printf("========================================\n");
    printf(" SIGNAL: %s\n", name);
    printf("========================================\n");

    printf("Sampling Frequency : %d Hz\n", FS);
    printf("Number of Samples  : %d\n", N);
    printf("Signal Duration    : %.3f seconds\n",
           (float)N / FS);

    printf("\n--- EXTRACTED FEATURES ---\n");

    printf("RMS Amplitude      : %.6f\n", f.rms);
    printf("Peak Amplitude     : %.6f\n", f.peak);
    printf("Crest Factor       : %.6f\n", f.crest);
    printf("Zero Crossing Rate : %.6f\n", f.zcr);

    printf("\n--- CLASSIFICATION ---\n");
    printf("Detected Pattern   : %s\n",
           classify_signal(f));

    printf("========================================\n");

    fflush(stdout);
}

/* --------------------------------------------------
   7. MAIN PROGRAM
   -------------------------------------------------- */

void main(void)
{
    printf("\n");
    printf("****************************************\n");
    printf(" TMS320C6745 DSP PROJECT\n");
    printf(" ACOUSTIC PATTERN RECOGNITION\n");
    printf("****************************************\n");

    printf("\nGenerating synthetic signals...\n");
    fflush(stdout);

    /* Test 1: Clap-like signal */
    generate_clap();
    run_test("SYNTHETIC CLAP");

    /* Test 2: Whistle-like signal */
    generate_whistle();
    run_test("SYNTHETIC WHISTLE");

    /* Test 3: Background noise */
    generate_background();
    run_test("SYNTHETIC BACKGROUND");

    printf("\n");
    printf("****************************************\n");
    printf(" ALL THREE TESTS COMPLETED\n");
    printf("****************************************\n");

    fflush(stdout);

    /* Keep the DSP program running */
    while (1)
    {
    }
}
