{
    "filename-parameters" : 
    {
	"output-format"         : "JSON",

        "output-file"           : "data_ctaux.json",
	"profiling-file"        : "profiling_classical.json",

        "spectrum-file"         : "data_CPE.json",
	"susceptibilities-file" : "data_susceptibilities.json"
    },

    "physics-parameters" :
    { 
        "beta"                      :  10,

	"adjust-chemical-potential" : "false", 
        "density"                   :  1.0,
        "chemical-potential"        : -1.0
    },

    "bilayer-model" : 
    {
	"t"  : 1,
	"t'" : 0,

	"tz" : 0,

	"U"  : 2,
        "U'" : 0,

	"V"  : 2,
	"V'" : 2
    },

    "DCA" : 
    {
    	"do-DCA+" : "false",

	"interacting-bands" : [0, 1],
	"DCA-iterations"    : 1,
	"DCA-mixing-factor" : 1.0,
	
	"cluster" : [[ 1, 0],
		     [ 0, 1]],

	"cluster-mapping" : 
	{
	   "k-mesh-refinement" : 3,
	   "quadrature-rule"   : 1,
	   "number-of-periods" : 0,

	   "precompute-Hamiltonian"      : "true",
	   "phi(k) integration accuracy" : 0.01,

	   "print-phi"                   : "false"
	},

	"lattice-mapping" : 
	{
	   "interpolation-method"         : "wannier-interpolation",

	   "deconvolution-tolerance"      : 0.01,
	   "max-deconvolution-iterations" : 16
	}
    },

    "Monte-Carlo-Integration" : 
    {
	"Sigma-file" : "zero",

	"warm-up-sweeps"         : 20,
	"sweeps-per-measurement" : 4,
	"measurements"           : 10000,

	"adaptive-double-counting" : "false",
	
	"RNG-seed" : 985456376,

	"MC-posix-parameters" : 
	{
	    "nr-walkers"       : 4,
	    "nr-accumulators"  : 4,
	    "additional-steps" : 0
	}
    },

    "CT-AUX-solver" : 
    {
	"submatrix-size"      : 16,
	"initial-matrix-size" : 256,

	"K-parameter"         : 100
    },

    "ED-solver-parameters" : 
    {   
    	"eigenvalue-cut-off" : 1e-6
    },

    "function-parameters" : 
    {
	"single-particle-functions" : 
	{
	    "H(k) grid-size"        : [8, 8],	

	    "time-intervals"        : 128,

	    "fermionic-frequencies" : 512,
	    "bosonic-frequencies"   : 128,
	    
	    "sp-cluster" : [[8, 8],
		      	    [8,-8]]
	},

	"two-particle-functions" : 
	{
	    "time-intervals"        : 32,

	    "fermionic-frequencies" : 16,
	    "bosonic-frequencies"   : 16,
	
	    "tp-cluster" : [[8, 8],
		      	    [8,-8]]
	},

	"real-axis-functions" :
	{
	    "lower-bound" : -10,
	    "upper-bound" :  10,

	    "nr-intervals" : 256,
	    "real-axis-off-set" : 0.01
	}
     },

    "equal-time-observables" : 
    {
        "do-equal-time-measurements" : "false"
    },

    "CPE-parameters" : 
    {
	"do-CPE" : "false",

	"max-CPE-iterations" : 1000,
	"max-CPE-error"      : 0.01,

	"number-of-matsubara-freqencies" : 32,

	"smoothing-factor" : 1,	
	
	"simulate-Gaussian-noise" : "true",
	"nr-of-samples"           : 100,
	"simulated-stddev"        : 0.01,

	"compute-free-spectrum"    : "false",
	"compute-lattice-spectrum" : "false",
	"compute-cluster-spectrum" : "true"
    }
}
