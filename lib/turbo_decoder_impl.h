/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_BLOCKSAT_TURBO_DECODER_IMPL_H
#define INCLUDED_BLOCKSAT_TURBO_DECODER_IMPL_H

#include <blocksat/turbo_decoder.h>

#include "Tools/types.h"
#include "Module/Interleaver/LTE/Interleaver_LTE.hpp"

#include "Module/Encoder/Turbo/Encoder_turbo.hpp"
#include "Module/Encoder/Encoder_sys.hpp"
#include "Module/Encoder/RSC/Encoder_RSC_generic_sys.hpp"

#include "Module/Decoder/Turbo/Decoder_turbo.hpp"
#include "Module/Decoder/RSC/BCJR/Seq/Decoder_RSC_BCJR_seq_very_fast.hpp"
#include "Module/Decoder/Turbo/Decoder_turbo_fast.hpp"

using namespace aff3ct;

namespace gr {
  namespace blocksat {

    class turbo_decoder_impl : public turbo_decoder
    {
     private:
      // Nothing to declare in this block.
			module::Encoder_RSC_generic_sys<B_8> *sub_enc;
  		module::Decoder_RSC_BCJR_seq_very_fast
				<B_8,Q_8,QD_8,tools::max<Q_8>,tools::max<QD_8>> * sub_dec;
			module::Interleaver_LTE<int> *interleaver;
  		module::Decoder_turbo_fast<B_8,Q_8> *dec;
      int d_input_size  ;
      int d_output_size ;

     public:
      turbo_decoder_impl(int N, int K);
      ~turbo_decoder_impl();

      // Where all the action really happens
      //int work(int noutput_items,
      //   gr_vector_const_void_star &input_items,
      //   gr_vector_void_star &output_items);
      int general_work(int noutput_items,
                       gr_vector_int& ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
      int fixed_rate_ninput_to_noutput(int ninput);
      int fixed_rate_noutput_to_ninput(int noutput);
      void forecast(int noutput_items,
                    gr_vector_int& ninput_items_required);

    };

  } // namespace blocksat
} // namespace gr

#endif /* INCLUDED_BLOCKSAT_TURBO_DECODER_IMPL_H */

