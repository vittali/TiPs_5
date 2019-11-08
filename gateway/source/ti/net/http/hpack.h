/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ti_net_http_HPACK__include
#define ti_net_http_HPACK__include

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @file ti/net/http/hpack.h
 *
 *  @brief Header compression for HTTP/2 (RFC 7541)
 */
#include <stdint.h>

#include "http2hdr.h"

#define HPACK_EINSUFFICIENTHEAP  (-101)
#define HPACK_EHUFFMANDECODEFAIL (-102)
#define HPACK_EINSUFFICIENTDATA  (-103)
#define HPACK_EDECODEERROR       (-104)

typedef struct DynamicTableEntry DynamicTableEntry;

/*! HPACK instance object */
typedef struct HPACK_Struct {
    DynamicTableEntry *decoderDynamicTable;
    uint32_t decoderDynamicTableSize;
    uint32_t decoderDynamicTableMaxSize;
} HPACK_Struct;

typedef HPACK_Struct *HPACK_Handle;

/*!
 *  @brief Initialize a new instance object inside the provided structure
 *
 *  @param[in]  hpack     Pointer to @ref HPACK_Struct to create instance
 */
extern void HPACK_construct(HPACK_Struct *hpack);

/*!
 *  @brief Destroy the instance object inside the provided structure
 *
 *  @param[in]  hpack     Pointer to @ref HPACK_Struct to destroy instance
 */
extern void HPACK_destruct(HPACK_Struct *hpack);

/*!
 *  @brief Compress the HTTP/2 header fields
 *
 *  @param[in]  hpack         Instance of an HPACK object
 *
 *  @param[in]  headersList   List of HTTP/2 Fields
 *
 *  @param[in]  len           Length of `headersList` list
 *
 *  @param[out]  headerBlock  Compressed header buffer generated by this
 *                            function.
 *
 *  @return the 'headerBlock' length on success or < 0 on failure
 */
extern int HPACK_encode(HPACK_Handle hpack, HTTP2Hdr_Field *headersList,
        uint32_t len, uint8_t **headerBlock);

/*!
 *  @brief Decompress to get the HTTP/2 header fields
 *
 *  @param[in]  hpack         Instance of an HPACK object
 *
 *  @param[in]  headerBlock   Compressed header buffer
 *
 *  @param[in]  len           Length of `headerBlock` list
 *
 *  @param[in]  headersList   Decompressed header field list generated by this
 *                            function
 *
 *  @return the number of headers in 'headersList' on success or < 0 on failure
 */
extern int HPACK_decode(HPACK_Handle hpack, uint8_t *headerBlock, uint32_t len,
        HTTP2Hdr_Field **headersList);

#ifdef __cplusplus
}
#endif
#endif
