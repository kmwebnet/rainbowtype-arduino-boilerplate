
#include "cryptoauthlib/atcacert_def.h"
#include "cert_chain.h"

uint8_t g_signer_1_ca_public_key[64] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const atcacert_def_t g_cert_def_0_root = {
    .type                   = CERTTYPE_X509,
    .template_id            = 0,
    .public_key_dev_loc     = {
        .zone      = DEVZONE_DATA,
        .slot      = 15,
        .is_genkey = 0,
        .offset    = 0,
        .count     = 72
    }
};

const atcacert_cert_element_t g_cert_elements_1_signer[] = {
    {
        .id         = "IssueDate",
        .device_loc = {
            .zone      = DEVZONE_DATA,
            .slot      = 14,
            .is_genkey = 0,
            .offset    = 35-13,
            .count     = 13
        },
        .cert_loc   = {
            .offset = 90,
            .count  = 13
        }
    },
    {
        .id         = "ExpireDate",
        .device_loc = {
            .zone      = DEVZONE_DATA,
            .slot      = 14,
            .is_genkey = 0,
            .offset    = 50-13,
            .count     = 13
        },
        .cert_loc   = {
            .offset = 105,
            .count  = 13
        }
    }
};
const uint8_t g_cert_template_1_signer[] = {
    0x30, 0x82, 0x01, 0xb8
};
const atcacert_def_t g_cert_def_1_signer = {
    .type                   = CERTTYPE_X509,
    .template_id            = 1,
    .chain_id               = 0,
    .private_key_slot       = 0,
    .sn_source              = SNSRC_STORED,
    .cert_sn_dev_loc        = {
        .zone      = DEVZONE_DATA,
        .slot      = 14,
        .is_genkey = 0,
        .offset    = 20-16,
        .count     = 16
    },
    .issue_date_format      = DATEFMT_RFC5280_UTC,
    .expire_date_format     = DATEFMT_RFC5280_UTC,
    .tbs_cert_loc           = {
        .offset = 4,
        .count  = 353
    },
    .expire_years           = 10,
    .public_key_dev_loc     = {
        .zone      = DEVZONE_DATA,
        .slot      = 11,
        .is_genkey = 0,
        .offset    = 0,
        .count     = 72
    },
    .comp_cert_dev_loc      = {
        .zone      = DEVZONE_DATA,
        .slot      = 12,
        .is_genkey = 0,
        .offset    = 0,
        .count     = 72
    },
    .std_cert_elements      = {
        { // STDCERT_PUBLIC_KEY
            .offset = 189,
            .count  = 64
        },
        { // STDCERT_SIGNATURE
            .offset = 369,
            .count  = 75
        },
        { // STDCERT_ISSUE_DATE
            .offset = 90,
            .count  = 13
        },
        { // STDCERT_EXPIRE_DATE
            .offset = 105,
            .count  = 13
        },
        { // STDCERT_SIGNER_ID
            .offset = 0,
            .count  = 0
        },
        { // STDCERT_CERT_SN
            .offset = 15,
            .count  = 16
        },
        { // STDCERT_AUTH_KEY_ID
            .offset = 337,
            .count  = 20
        },
        { // STDCERT_SUBJ_KEY_ID
            .offset = 304,
            .count  = 20
        }
    },
    .cert_elements          = g_cert_elements_1_signer,
    .cert_elements_count    = sizeof(g_cert_elements_1_signer) / sizeof(g_cert_elements_1_signer[0]),
    .cert_template          = g_cert_template_1_signer,
    .cert_template_size     = sizeof(g_cert_template_1_signer),
    .ca_cert_def            = &g_cert_def_0_root,
};


const atcacert_cert_element_t g_cert_elements_2_device[] = {
    {
        .id         = "common_name",
        .device_loc = {
            .zone      = DEVZONE_DATA,
            .slot      = 13,
            .is_genkey = 0,
            .offset    = 0,
            .count     = 18
        },
        .cert_loc   = {
            .offset = 151,
            .count  = 18
        }
    }
};

const uint8_t g_cert_template_2_device[] = {
    0x30, 0x82, 0x01, 0x9b
};
atcacert_def_t g_cert_def_2_device = {
    .type                   = CERTTYPE_X509,
    .template_id            = 2,
    .chain_id               = 0,
    .private_key_slot       = 0,
    .sn_source              = SNSRC_PUB_KEY_HASH,
    .cert_sn_dev_loc        = {
        .zone      = DEVZONE_NONE,
        .slot      = 0,
        .is_genkey = 0,
        .offset    = 0,
        .count     = 0
    },
    .issue_date_format      = DATEFMT_RFC5280_UTC,
    .expire_date_format     = DATEFMT_RFC5280_GEN,
    .tbs_cert_loc           = {
        .offset = 4,
        .count  = 324
    },
    .expire_years           = 0,
    .public_key_dev_loc     = {
        .zone      = DEVZONE_DATA,
        .slot      = 0,
        .is_genkey = 1,
        .offset    = 0,
        .count     = 64
    },
    .comp_cert_dev_loc      = {
        .zone      = DEVZONE_DATA,
        .slot      = 10,
        .is_genkey = 0,
        .offset    = 0,
        .count     = 72
    },
    .std_cert_elements      = {
        { // STDCERT_PUBLIC_KEY
            .offset = 196,
            .count  = 64
        },
        { // STDCERT_SIGNATURE
            .offset = 340,
            .count  = 75
        },
        { // STDCERT_ISSUE_DATE
            .offset = 91,
            .count  = 13
        },
        { // STDCERT_EXPIRE_DATE
            .offset = 0,
            .count  = 0
        },
        { // STDCERT_SIGNER_ID
            .offset = 0,
            .count  = 0
        },
        { // STDCERT_CERT_SN
            .offset = 15,
            .count  = 16
        },
        { // STDCERT_AUTH_KEY_ID
            .offset = 308,
            .count  = 20
        },
        { // STDCERT_SUBJ_KEY_ID
            .offset = 275,
            .count  = 20
        }
    },
    .cert_elements          = g_cert_elements_2_device,
    .cert_elements_count    = sizeof(g_cert_elements_2_device) / sizeof(g_cert_elements_2_device[0]),
    .cert_template          = g_cert_template_2_device,
    .cert_template_size     = sizeof(g_cert_template_2_device),
    .ca_cert_def            = &g_cert_def_1_signer,
};

