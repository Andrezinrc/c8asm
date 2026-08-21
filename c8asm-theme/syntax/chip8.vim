if exists("b:current_syntax") | finish | endif

syn keyword chip8Instruction ld add sub subn or and xor shr shl cls drw rnd

syn keyword chip8InstructionJump jp jmp call ret

syn keyword chip8Conditional se sne skp sknp

syn keyword chip8Define alias spr

syn match chip8Reg          '\v<v[0-9a-fA-F]>'
syn match chip8IndexReg     '\v<i>'
syn match chip8MemRef       '\v<\[i\]>'
syn match chip8SpecialReg   '\v<(dt|st|k|f|b)>'

syn match chip8Hex          '\v0x[0-9a-fA-F]+'
syn match chip8Num          '\v<\d+>'

syn match chip8Label        '\v^[a-zA-Z_][a-zA-Z0-9_]*:'
syn match chip8Comment      ';.*$'

hi def link chip8Instruction     Normal
hi def link chip8InstructionJump Normal
hi def link chip8Conditional     Normal
hi def link chip8Define          Normal

hi def link chip8Reg             Identifier
hi def link chip8Label           Function
hi def link chip8Comment         Comment
hi def link chip8Hex             Number
hi def link chip8Num             Number

let b:current_syntax = "chip8"
