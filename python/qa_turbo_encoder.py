#!/usr/bin/env python2
# -*- coding: utf-8 -*-
# 
# Copyright 2017 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import blockstream_swig as blockstream

class qa_turbo_encoder (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        N = 18444
        K = 6144
        in_vec = [1%2 for i in range(K)]
        # set up fg
        src = blocks.vector_source_b(in_vec)
        dut = blockstream.turbo_encoder(N, K);
        snk = blocks.vector_sink_b()
        self.tb.connect (src, dut, snk)
        self.tb.run ()

        # check data
        res_sym_out = snk.data ()
        print(res_sym_out)


if __name__ == '__main__':
    gr_unittest.run(qa_turbo_encoder, "qa_turbo_encoder.xml")
