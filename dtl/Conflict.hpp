/**
   dtl -- Diff Template Library
   
   In short, Diff Template Library is distributed under so called "BSD license",
   
   Copyright (c) 2015 Tatsuhiko Kubo <cubicdaiya@gmail.com>
   All rights reserved.
   
   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:
   
   * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
   
   * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
   
   * Neither the name of the authors nor the names of its contributors
   may be used to endorse or promote products derived from this software 
   without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* If you use this library, you must include dtl.hpp only. */

#ifndef DTL_CONFLICT_H
#define DTL_CONFLICT_H

namespace dtl {
    
    /**
     * conflict handling class template
     * sequence must support random_access_iterator.
     */
    template <typename elem, typename sequence = vector< elem > >
    class Conflict
    {
    private :
        dtl_typedefs(elem, sequence)
        elemVec& finalSeq;
        elemVec  confSeqA;
        elemVec  confSeqB;
        elem     markA;
        elem     markB;
        elem     markC;
        bool     inConflictBlock;
    public :
        Conflict (elemVec& seq,
                  elem _confMarkA,
                  elem _confMarkB,
                  elem _confMarkC) : finalSeq(seq),
                                     markA(_confMarkA),
                                     markB(_confMarkB),
                                     markC(_confMarkC),
                                     inConflictBlock(false) {
        }
        
        ~Conflict() {}
        
        void handleElem(sesElemVec_iter* A, sesElemVec_iter* B, bool conflict) {
            if (conflict && !inConflictBlock) {
                confSeqA.clear();
                confSeqB.clear();
                if (A != nullptr)
                    confSeqA.push_back((*A)->first);
                if (B != nullptr)
                    confSeqB.push_back((*B)->first);
            } else if (conflict && inConflictBlock) {
                if (A != nullptr)
                    confSeqA.push_back((*A)->first);
                if (B != nullptr)
                    confSeqB.push_back((*B)->first);
            } else if (!conflict && inConflictBlock) {
                finalSeq.push_back(markA);
                for (elem e : confSeqA)
                    finalSeq.push_back(e);
                finalSeq.push_back(markB);
                for (elem e : confSeqB)
                    finalSeq.push_back(e);
                finalSeq.push_back(markC);
            }
            inConflictBlock = conflict;
        }
    };
}

#endif // DTL_CONFLICTCONFLICT_H
