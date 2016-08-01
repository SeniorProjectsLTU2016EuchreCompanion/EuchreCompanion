/*
* File to test and explore libnfc
*/

#include <stdlib.h>
#include <nfc/nfc.h>

static void
print_card(const uint8_t *pbtData, const size_t szBytes)
{
    //compare data to card values and print card
    if (pbtData[0] == 0xb1) {
        printf("Jack of Spades\n");
    }
    else if (pbtData[0] == 0x61) {
        printf("Ace of Spades\n");
    }
    else {
        printf("Card Not Found");
    }
}

int main(int argc, const char *argv[])
{
    nfc_device *pnd;
    nfc_target nt;

    nfc_context *context;

    nfc_init(&context);
    if (context == NULL) {
        printf("Unable to init libnfc (malloc)\n");
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

    for (int i = 0; i < 2; i++) {
        if (nfc_initiator_select_passive_target(pnd, nmMifare, NULL, 0, &nt) > 0) {
            printf("The following (NFC) Card was found:\n");
            print_card(nt.nti.nai.abtUid, nt.nti.nai.szUidLen);
        }
        while (0 == nfc_initiator_target_is_present(pnd, NULL)){}
    }

    nfc_close(pnd);

    nfc_exit(context);

    exit(EXIT_SUCCESS);
}
