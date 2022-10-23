                section        .text

                global         _print

_print:
                pushad

                mov                esi, [esp + reg_total_size + 12]
                call               parse_hex_128

                call               resolve_sign_of_hex_128
                call               resolve_negative_hex_128
                call               converting_to_decimal

                mov                esi, [esp + reg_total_size + 8]
                call               parse_format

                mov                edi, [esp + reg_total_size + 4]
                call               resolve_format

                mov                byte [edi], 0

                popad
                ret

;;;;
;; Reading and parsing 128-bit hex
;;;;

parse_hex_128:
                xor                ebx, ebx
                xor                ebp, ebp
                xor                ecx, ecx
                xor                edx, edx
                xor                edi, edi

                cmp                byte [esi], '-'
                jne                .loop_start
                inc                ebx
                inc                esi
.loop_start:
                cmp                byte [esi], 0
                je                 .end
.loop:
                shld               ebp, ecx, 4
                shld               ecx, edx, 4
                shld               edx, edi, 4
                shl                edi, 4
                call               parse_hex_digit
                or                 edi, eax
                inc                esi
                cmp                byte [esi], 0
                jne                .loop
.end:
                ret

parse_hex_digit:
                xor                eax, eax
                mov                al, [esi]
                cmp                al, '0'
                jb                 .end
                cmp                al, '9'
                ja                 .capital_letter
                sub                al, '0'
                ret
.capital_letter:
                cmp                al, 'A'
                jb                 .end
                cmp                al, 'F'
                ja                 .letter
                sub                al, 'A'
                add                al, 0xa
                ret
.letter:
                cmp                al, 'a'
                jb                 .end
                cmp                al, 'f'
                ja                 .end
                sub                al, 'a'
                add                al, 0xa
.end:
                ret

;;;;
;; Work with negative hexs
;;;;

resolve_sign_of_hex_128:
                test               ebx, ebx
                jz                 .end
                call               negate_hex_128
.end:
                ret

resolve_negative_hex_128:
                xor                ebx, ebx
                test               ebp, last_bit
                jz                 .end
                inc                ebx
                call               negate_hex_128
.end:
                ret

negate_hex_128:
                not                ebp
                not                ecx
                not                edx
                not                edi
                clc
                adc                edi, 1
                adc                edx, 0
                adc                ecx, 0
                adc                ebp, 0
                ret

;;;;
;; Converting 128-hex to decimal representation
;;;;

converting_to_decimal:
                push               ebx
                sub                esp, 4 * 4

                mov                [esp], ebp
                mov                [esp + 4], ecx
                mov                [esp + 8], edx
                mov                [esp + 12], edi

                mov                ebx, 10
                xor                ecx, ecx

.loop:
                xor                edx, edx

                mov                eax, [esp]
                div                ebx
                mov                [esp], eax

                mov                eax, [esp + 4]
                div                ebx
                mov                [esp + 4], eax

                mov                eax, [esp + 8]
                div                ebx
                mov                [esp + 8], eax

                mov                eax, [esp + 12]
                div                ebx
                mov                [esp + 12], eax

                add                dl, '0'
                mov                [decimal + ecx], dl
                inc                ecx

                cmp                dword [esp], 0
                jne                .loop
                cmp                dword [esp + 4], 0
                jne                .loop
                cmp                dword [esp + 8], 0
                jne                .loop
                cmp                dword [esp + 12], 0
                jne                .loop

                add                esp, 4 * 4
                pop                ebx
                ret

;;;;
;; Reading and parsing format string, setting flags
;;;;

parse_format:
                xor                eax, eax
                dec                esi
.loop:
                inc                esi
                cmp                byte [esi], 0
                je                 .end
                cmp                byte [esi], '1'
                jb                 .set_flag
                cmp                byte [esi], '9'
                ja                 .set_flag
                jmp                .parse_width
.set_flag:
                cmp                byte [esi], '0'
                je                 .set_zero
                cmp                byte [esi], '+'
                je                 .set_plus
                cmp                byte [esi], '-'
                je                 .set_minus
.set_space:
                or                 bh, space_flag
                jmp                .loop
.set_zero:
                or                 bh, zero_flag
                jmp                .loop
.set_plus:
                or                 bh, plus_flag
                jmp                .loop
.set_minus:
                or                 bh, minus_flag
                jmp                .loop
.parse_width:
                mov                edx, 10
                mul                edx
                mov                dl, [esi]
                sub                dl, '0'
                add                eax, edx
                inc                esi
                cmp                byte [esi], '0'
                jb                 .end
                cmp                byte [esi], '9'
                ja                 .end
                cmp                byte [esi], 0
                jne                .parse_width
.end:
                ret

;;;;
;; Resolving format, invoking print functions
;;;;

resolve_format:
                mov                edx, eax
                test               bl, zero_flag
                jnz                .set_sign
                test               bh, plus_flag
                jnz                .set_plus
                test               bh, space_flag
                jnz                .set_space
                jmp                .set_sign
.set_space:
                or                 bl, minus_flag
                jmp                .set_sign
.set_plus:
                or                 bl, plus_flag
.set_sign:
                test               bl, (zero_flag | plus_flag | minus_flag)
                jz                 .no_sign
                dec                edx
                cmp                edx, ecx
                jge                .no_fix
                mov                edx, ecx
.no_fix:
                inc                edx
                jmp                .end
.no_sign:
                cmp                edx, ecx
                jge                .end
                mov                edx, ecx
.end:
                test               bh, minus_flag
                jz                 .left
                call               right_padding_print
                ret
.left:
                call               left_padding_print
                ret

;;;;
;; Printing result to result buffer
;;;;

right_padding_print:
                call               print_sign
                cmp                edx, ecx
                jge                .no_fix
                inc                edx
.no_fix
                sub                edx, ecx
.digits:
                mov                al, [decimal + ecx - 1]
                mov                [edi], al
                dec                ecx
                inc                edi
                test               ecx, ecx
                jnz                .digits

                test               edx, edx
                jz                 .end
.spaces:
                mov                byte [edi], ' '
                inc                edi
                dec                edx
                test               edx, edx
                jnz                .spaces
.end:
                ret

left_padding_print:
                xor                esi, esi
                mov                ebp, edx
                dec                ebp
.digits:
                mov                al, [decimal + esi]
                mov                [edi + ebp], al
                inc                esi
                dec                ebp
                cmp                esi, ecx
                jb                 .digits

                test               bh, zero_flag
                jnz                .zeros_start
                add                ebp, edi

                inc                ebp
                test               bl, (zero_flag | plus_flag | minus_flag)
                jz                 .spaces_start
                dec                ebp

                inc                edx
                push               edi
                mov                edi, ebp
                call               print_sign
                pop                edi
.spaces_start:
                mov                al, ' '
                jmp                .padding_loop
.zeros_start:
                call               print_sign
                lea                ebp, [edx + edi]
                sub                ebp, ecx

                mov                edx, ecx
                mov                al, '0'
.padding_loop:
                cmp                edi, ebp
                je                 .end
                jg                 .fix
                mov                byte [edi], al
                inc                edi
                jmp                .padding_loop
.fix
                inc                ebp
                jmp                .padding_loop
.end:
                add                edi, edx
                ret

print_sign:
                test               bl, (zero_flag | plus_flag | minus_flag)
                jz                 .end
                test               bl, zero_flag
                jnz                .minus
                test               bl, plus_flag
                jnz                .plus
                mov                byte [edi], ' '
                jmp                .after_print
.minus:
                mov                byte [edi], '-'
                jmp                .after_print
.plus:
                mov                byte [edi], '+'
.after_print:
                inc                edi
                dec                edx
.end:
                ret

;;;;
;; Constants and static memory
;;;;

                section .bss

decimal:        resb    40 ;; Enough for decimal representation of 128-bit hex

                section .rodata

reg_total_size: equ     (4 * 8)
zero_flag:      equ     (1 << 0)
plus_flag:      equ     (1 << 1)
minus_flag:     equ     (1 << 2)
space_flag:     equ     (1 << 3)
last_bit:       equ     (1 << 31)
