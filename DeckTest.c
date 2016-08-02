/*
* Program to test the deck make sure cards are read correctly
*/

#include <stdlib.h>
#include <nfc/nfc.h>

static void
print_card(const uint8_t *pbtData, const size_t szBytes)
{

}

int main(int argc, const char *argv[])
{
    nfc_device *pnd;
    nfc_target nt;

    nfc_context *context;

    nfc_init(&context);
    if(context == NULL) {
        printf("unable to init (malloc)\n");
        exit(EXIT_FAILURE);
    }

    pnd = nfc_open(context, NULL);

    if (pnd == NULL) {
        printf("ERROR: %s\n", "Unable to open NFC Device.");
        exit(EXIT_FAILURE);
    }

    if (nfc_initiator_init(pnd) < 0) {
        nfc_perror(pnd, "nfc_initiator_init");
        exit(EXIT_FAILURE);
    }

    printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));

    const nfc_modulation nmMifare = {
        .nmt = NMT_ISO14443A,
        .nbr = NBR_106,
    };

    for(int i = 0; i < 24; i++) {
        if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0) {
            printf("The following (NFC) card was found:\n");
            print_card(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
        }
        while (0 == nfc_initiator_target_is_present(pnd, NULL)){}
    }

    nfc_close(pnd);

    nfc_exit(context);

    exit(EXIT_SUCCESS);   
}