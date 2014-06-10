
import commands
import os
import sys
import time

import matplotlib
matplotlib.use('Agg')

import matplotlib.mlab as mlab

from numpy import *

#from numpy import matrix

import shutil
import os

from pylab import *

import json

import scipy

from scipy.stats import norm

do_QMC = True

if(do_QMC):
    filename1 = "data_QMC.json"#raw_input('Please enter input-filename1 : ...\n\n\t' )
    #filename1 = "data_HTS.json"#raw_input('Please enter input-filename1 : ...\n\n\t' )
    filename2 = "data_ED.json"#raw_input('Please enter input-filename1 : ...\n\n\t' )

if(not do_QMC):
    filename1 = "data_ctaux_1.json"#raw_input('Please enter input-filename1 : ...\n\n\t' )
    filename2 = "data_sshyb_1.json"#raw_input('Please enter input-filename1 : ...\n\n\t' )

FIGURE_EXTENSION = ".png" # ".png" ".pdf"

left   = 0.125 # the left side of the subplots of the figure
right  = 0.9   # the right side of the subplots of the figure
bottom = 0.1   # the bottom of the subplots of the figure
top    = 0.9   # the top of the subplots of the figure
wspace = 0.2   # the amount of width reserved for blank space between subplots
hspace = 0.8   # the amount of height reserved for white space between subplots

#for parameter in data['parameters']['physics-parameters']:
#    print parameter

F = figure(1)
DefaultSize = F.get_size_inches()
# F.set_size_inches( (DefaultSize[0]*2.5, DefaultSize[1]*2) )
F.set_size_inches( (DefaultSize[0]*4, DefaultSize[1]*3) )

def my_format(x):
    return ('%.2g' % x)


def read_function_name(line):

    function_name_stri = '{' + line[0:len(line)-2] + '}'
    function_name_json = json.loads(function_name_stri)
    function_name = function_name_json['name']
    return function_name

def read_function_matrix(file):
    
    stringmatrix = '{'

    for line in file:
        if "data" in line:
            stringmatrix = stringmatrix+line

            for line in file:
                if "}" in line:
                    break
                else:
                    stringmatrix = stringmatrix+line
            break        

    stringmatrix = stringmatrix+'}'
    
    return stringmatrix

def plot_band_structure(domains, function_name, function_matrix1, function_matrix2):

    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)
    
    bands = max(function_matrix1[:,0]) + 1;
    spin  = max(function_matrix1[:,1]) + 1;
    kp    = max(function_matrix1[:,2]) + 1;

    figure(num=None)
    
    for i in range(0,bands):
        
        bs1 = []
        bs2 = []
        
        for r in range(0,kp):
            bs1.append(function_matrix1[int(i+0*bands + r*bands*spin),3])
            bs2.append(function_matrix2[int(i+0*bands + r*bands*spin),3])

        grid(True)
        plot(bs1, 'k') 
        plot(bs2, '-r') 

    ylabel('Energy (eV)')
    xticks ([0, 100, 200, 300],
            ['$\Gamma$', 'K', 'X', '$\Gamma$'])

    legend(('model-Hamiltonian', 'H(k)'), 'upper right', shadow=True, fancybox=True)

    savefig('./pictures/' + function_name + '/' + function_name + FIGURE_EXTENSION)
    
    bs1 = [] 
    bs2 = [] 

def plot_leading_eigenvector(domains,function_name, function_matrix1, function_matrix2):

    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)

    freq_dmn_ext = domains["extended_vertex_frequency_domain"]
    freq_dmn_com = domains["compact_vertex_frequency_domain"]

    bands = max(function_matrix1[:,0]) + 1;
    sites = max(function_matrix1[:,2]) + 1;
    freqs = max(function_matrix1[:,3]) + 1;

    for i_0 in range(0,bands):
        for i_1 in range(0,bands):
            for k_0 in range(0,sites):

                figure(num=None)
                
                vec_re_1 = []
                vec_im_1 = []
                vec_re_2 = []
                vec_im_2 = []

                for w_0 in range(0,freqs):
                    for w_1 in range(0,size(freq_dmn_com)):
                        if(freq_dmn_ext[w_0] == freq_dmn_com[w_1]):
                            vec_re_1.append(function_matrix1[int(i_0 + i_1*bands + k_0*bands*bands + w_0*bands*bands*sites),4])
                            vec_im_1.append(function_matrix1[int(i_0 + i_1*bands + k_0*bands*bands + w_0*bands*bands*sites),5])
                            vec_re_2.append(function_matrix2[int(i_0 + i_1*bands + k_0*bands*bands + w_0*bands*bands*sites),4])
                            vec_im_2.append(function_matrix2[int(i_0 + i_1*bands + k_0*bands*bands + w_0*bands*bands*sites),5])

                grid(True)
                plot(freq_dmn_com, vec_re_1, 'k')
                plot(freq_dmn_com, vec_im_1, 'r')
                plot(freq_dmn_com, vec_re_2, 'ok')
                plot(freq_dmn_com, vec_im_2, 'or')

                savefig('./pictures/' + function_name +'/' + function_name + '_' + str(i_0) + '_' + str(i_1) + '_' + str(k_0) + FIGURE_EXTENSION)


def plot_wn_function(domains, function_name, function_matrix1, function_matrix2):

    Nb_freqs=50

    #freq_dmn = array(domains["frequency_domain"])
    freq_dmn = domains["domains"]["frequency-domain"]["elements"]

    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)

    bands = max(function_matrix1[:,0]) + 1;
    sites = max(function_matrix1[:,4]) + 1;
    times = max(function_matrix1[:,5]) + 1;

    freq_dmn_tmp           = []

    function_matrix_real1  = []
    function_matrix_imag1  = []
    function_matrix_real2  = []
    function_matrix_imag2  = []

    f_error_re = []
    f_error_im = []
    

    for r in range(0,sites):   
        f=figure(num=None)#, figsize=(12,10))
        for i in range(0,bands):
            for j in range(0,bands):

                subplot(bands, bands, i+1+bands*j)

                freq_dmn_tmp           = []

                function_matrix_real1  = []
                function_matrix_imag1  = []
                function_matrix_real2  = []
                function_matrix_imag2  = []

                f_error_re = []
                f_error_im = []

                for l in range(0,2*Nb_freqs):

                    l_new = times/2-Nb_freqs+l

                    freq_dmn_tmp.append(freq_dmn[int(l_new)])

                    f0_re = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6]
                    f0_im = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7]

                    f1_re = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6]
                    f1_im = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7]

                    function_matrix_real1.append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6])
                    function_matrix_imag1.append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7])
                    function_matrix_real2.append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6])
                    function_matrix_imag2.append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7])

                    f_error_re.append(f0_re-f1_re)
                    f_error_im.append(f0_im-f1_im)

                grid(True)

                plot(freq_dmn_tmp, function_matrix_real1, 'og', label=filename1)
                plot(freq_dmn_tmp, function_matrix_imag1, 'ok', label=filename1)
                plot(freq_dmn_tmp, function_matrix_real2, '.-b', label=filename2)
                plot(freq_dmn_tmp, function_matrix_imag2, '.-r', label=filename2)
                
                legend(loc='upper right')

                #legend(('Re '+filename1, 'Im '+filename1,'Re '+filename2, 'Im '+filename2), 'upper right', shadow=False, fancybox=False, prop={'size':16})

        savefig('./pictures/' + function_name + '/' + function_name + '_'+ str(r) + FIGURE_EXTENSION)
                
    f=figure(2)

    for i in range(0,bands):
        for j in range(0,bands):

            


            total_re = []
            total_im = []

            for r in range(0,sites):
                for l in range(times/2,times):

                    f0_re = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6]
                    f0_im = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7]

                    f1_re = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6]
                    f1_im = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7]

                    total_re.append((f0_re-f1_re))
                    total_im.append((f0_im-f1_im))

            print "start"
            subplot(bands, 2*bands, 1+2*(i+bands*j))                    
            #subplot(121)
            (mu, sigma) = norm.fit(total_re)
            n, bins, patches = hist(total_re, 100, normed=1, facecolor='red', alpha=0.75)
            y = mlab.normpdf( bins, mu, sigma)
            l = plt.plot(bins, y, 'r-', linewidth=2)#,  label=r'$Re[\epsilon] \mu=%.3f,\ \sigma=%.3f$' %(mu, sigma))
            xlim(mu-3*sigma, mu+3*sigma)
            title(r'$Re[\epsilon] \mu=%.3f,\ \sigma=%.3f$' %(mu, sigma))
            
            legend(loc='upper right')

            print "start"
            subplot(bands, 2*bands, 2+2*(i+bands*j))                    
            #subplot(122)
            (mu, sigma) = norm.fit(total_im)
            n, bins, patches = hist(total_im, 100, normed=1, facecolor='black', alpha=0.75)
            y = mlab.normpdf( bins, mu, sigma)
            l = plt.plot(bins, y, 'k-', linewidth=2)#,  label=r'$Re[\epsilon] \mu=%.3f,\ \sigma=%.3f$' %(mu, sigma))
            xlim(mu-3*sigma, mu+3*sigma)
            title(r'$Im[\epsilon] \mu=%.3f,\ \sigma=%.3f$' %(mu, sigma))
    
            legend(loc='upper right')

    savefig('./pictures/' + function_name + '/errors'+FIGURE_EXTENSION)

    f=figure(3)
    #title(r"$U=-4$, $\mu=0$, $\beta=10$, # sweeps=20")

    for i in range(0,bands):
        for j in range(0,bands):

            subplot(bands, bands, i+1+bands*j)

            for r in range(0,sites):   

                freq_dmn_tmp           = []

                function_matrix_real1  = []
                function_matrix_imag1  = []
                function_matrix_real2  = []
                function_matrix_imag2  = []

                f_error_re = []
                f_error_im = []

                for l in range(0,2*Nb_freqs):

                    l_new = times/2-Nb_freqs+l

                    freq_dmn_tmp.append(freq_dmn[int(l_new)])

                    f0_re = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6]
                    f0_im = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7]

                    f1_re = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6]
                    f1_im = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7]

                    function_matrix_real1.append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6])
                    function_matrix_imag1.append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7])
                    function_matrix_real2.append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6])
                    function_matrix_imag2.append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7])

                    f_error_re.append(f0_re-f1_re)
                    f_error_im.append(f0_im-f1_im)

                grid(True)

                plot(freq_dmn_tmp, function_matrix_real1, 'og')
                plot(freq_dmn_tmp, function_matrix_imag1, 'ok')
                plot(freq_dmn_tmp, function_matrix_real2, '.-b')
                plot(freq_dmn_tmp, function_matrix_imag2, '.-r')

    #legend(('Re '+filename1, 'Im '+filename1,'Re '+filename2, 'Im '+filename2), 'upper right', shadow=False, fancybox=False, prop={'size':16})

    savefig('./pictures/' + function_name + '/0_overview' + FIGURE_EXTENSION)


def plot_w_function(domains, function_name, function_matrix1, function_matrix2):

    freq_dmn = array(domains["Pade_real_frequency_domain"])

    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)

    bands = max(function_matrix1[:,0]) + 1;
    sites = max(function_matrix1[:,4]) + 1;
    times = max(function_matrix1[:,5]) + 1;

    freq_dmn_tmp           = []

    function_matrix_real1  = []
    function_matrix_imag1  = []
    function_matrix_real2  = []
    function_matrix_imag2  = []

    f_error_re = []
    f_error_im = []
    

    for r in range(0,sites):   
        f=figure(num=None, figsize=(12,6))
        for i in range(0,bands):
            for j in range(0,bands):

                #subplot(bands, bands, i+1+bands*j)


#                 diff_re = 0
#                 diff_im = 0

                freq_dmn_tmp           = []

                function_matrix_real1  = []
                function_matrix_imag1  = []
                function_matrix_real2  = []
                function_matrix_imag2  = []

                f_error_re = []
                f_error_im = []

                for l in range(0,times):

                    l_new = l

                    freq_dmn_tmp.append(freq_dmn[int(l_new)])

                    f0_re = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6]
                    f0_im = function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7]

                    f1_re = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6]
                    f1_im = function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7]

                    function_matrix_real1.append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6])
                    function_matrix_imag1.append(-function_matrix1[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7])
                    function_matrix_real2.append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),6])
                    function_matrix_imag2.append(-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites),7])

                    f_error_re.append(f0_re-f1_re)
                    f_error_im.append(f0_im-f1_im)

#                     if(freq_dmn[int(l_new)]>0):
#                         total_re.append(f0_re-f1_re)
#                         total_im.append(f0_im-f1_im)

#                     val = (function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6]-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
#                     diff_re = diff_re + val*val/times

#                     val = (function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7]-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])
#                     diff_im = diff_im + val*val/times
                    


                grid(True)

                subplot(121)
                plot(freq_dmn_tmp, function_matrix_real2, '-k', label = 'Re '+filename2)
                plot(freq_dmn_tmp, function_matrix_real1, '-r', label = 'Re '+filename1)

                legend(loc='lower right', shadow=False, fancybox=False, prop={'size':12})

                subplot(122)
                semilogy(freq_dmn_tmp, function_matrix_imag2, '-k', label = 'Im '+filename2)
                semilogy(freq_dmn_tmp, function_matrix_imag1, '-r', label = 'Im '+filename1)
                legend(loc='lower right', shadow=False, fancybox=False, prop={'size':12})
                

                #a1 = axes([.2, .2, .2, .2], axisbg='w')
                #n, bins, patches = hist(f_error_re, 20, normed=1)
                #title('error Re')
                #setp(a1, xticks=[])#, yticks=[])

                #a2 = axes([.6, .2, .2, .2], axisbg='w')
                #n, bins, patches = hist(f_error_im, 20, normed=1)
                #title('error Im')
                #setp(a2, xticks=[])

#                 f.text(0.2,0.75,'diff Re =' + str(diff_re))
#                 f.text(0.2,0.70,'diff Im =' + str(diff_im))

#                 savefig('./pictures/' + function_name + '/' + function_name + '_'+ str(r) + '_'+ str(i) + '_' + str(j)+FIGURE_EXTENSION)
                
                #xlim(-8,8)

        savefig('./pictures/' + function_name + '/' + function_name + '_'+ str(r) + FIGURE_EXTENSION)
                

def plot_phi_wn_function(domains, function_name, function_matrix1, function_matrix2):

    Nb_freqs=50

    freq_dmn = array(domains["frequency_domain"])

    print freq_dmn
        

    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)

    phis  = max(function_matrix1[:,0]) + 1;
    bands = max(function_matrix1[:,1]) + 1;
    sites = max(function_matrix1[:,5]) + 1;
    freqs = max(function_matrix1[:,6]) + 1;

    freq_dmn_tmp           = []
    function_matrix_real1  = []
    function_matrix_imag1  = []
    function_matrix_real2  = []
    function_matrix_imag2  = []
    
    for phi in range(0,phis):
        for i in range(0,bands):
        #for j in range(0,bands):
            j=i
            for r in range(0,sites):

                diff_re = 0
                diff_im = 0

                for l in range(0,2*Nb_freqs):
                    #print int(times/2-Nb_freqs+l)

                    l_new = freqs/2-Nb_freqs+l
                    freq_dmn_tmp.append(freq_dmn[int(l_new)])

                    function_matrix_real1 .append(function_matrix1[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites)),7])
                    function_matrix_imag1 .append(function_matrix1[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites)),8])
                    function_matrix_real2 .append(function_matrix2[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites)),7])
                    function_matrix_imag2 .append(function_matrix2[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l_new*4*bands*bands*sites)),8])

                    val = (function_matrix1[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites)),7]
                           -function_matrix2[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites)),7])
                    diff_re = diff_re + val*val/freqs

                    val = (function_matrix1[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites)),8]
                           -function_matrix2[int(phi + phis*(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites)),8])
                    diff_im = diff_im + val*val/freqs
                    
                f=figure(num=None)

                grid(True)
                plot(freq_dmn_tmp, function_matrix_real1, '-g')#, alpha=0.1)
                plot(freq_dmn_tmp, function_matrix_imag1, '--g')
                plot(freq_dmn_tmp, function_matrix_real2, '-b')
                plot(freq_dmn_tmp, function_matrix_imag2, '--b')

                f.text(0.6,0.75,'diff Re $\:=\: $' + str(diff_re))
                f.text(0.6,0.70,'diff Im $\:=\: $' + str(diff_im))

                savefig('./pictures/' + function_name + '/' + function_name + '_'+ str(r) + '_'+ str(i) + '_' + str(j)+FIGURE_EXTENSION)
                
                freq_dmn_tmp           = []
                function_matrix_real1  = []
                function_matrix_imag1  = []
                function_matrix_real2  = []
                function_matrix_imag2  = []


def plot_tau_function(domains, function_name, function_matrix1, function_matrix2):

    time_dmn = domains["domains"]["time-domain"]["elements"]
        
    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)
    
    bands = max(function_matrix1[:,0]) + 1;
    sites = max(function_matrix1[:,4]) + 1;
    times = max(function_matrix1[:,5]) + 1;

    print bands
    print sites
    print times

    function_matrix_real1  = []
    function_matrix_imag1  = []
    function_matrix_real2  = []
    function_matrix_imag2  = []

    for i in range(0,bands):
        for j in range(0,bands):
            for r in range(0,sites):

                diff_re = 0
                diff_im = 0

                for l in range(0,times):
                    function_matrix_real1 .append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
                    #function_matrix_imag1 .append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])
                    function_matrix_real2 .append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
                    #function_matrix_imag2 .append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])

                    val = (function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6]-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
                    diff_re = diff_re + val*val/times

#                     val = (function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7]-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])
#                     diff_im = diff_im + val*val/times
                    
                f=figure(num=None)

                grid(True)
                plot(time_dmn, function_matrix_real1, 'bo-')
                #plot(time_dmn, function_matrix_imag1, 'ok')
                plot(time_dmn, function_matrix_real2, '.r-')
                #plot(time_dmn, function_matrix_imag2, '+r')

                legend((filename1, filename2), 'upper right', shadow=False, fancybox=False, prop={'size':16})

                #f.text(0.2,0.75,'diff Re =' + str(diff_re))
                #f.text(0.2,0.70,'diff Im =' + str(diff_im))

                #legend(('Re '+filename1, 'Im '+filename1,'Re '+filename2, 'Im '+filename2), 'upper right', shadow=True, fancybox=True)

                savefig('./pictures/' + function_name + '/' + function_name + '_'+ str(r) + '_'+ str(i) + '_' + str(j)+FIGURE_EXTENSION)
                
                function_matrix_real1  = []
                function_matrix_imag1  = []
                function_matrix_real2  = []
                function_matrix_imag2  = []

    for i in range(0,bands):
        for j in range(0,bands):

            f=figure(num=None)

            for r in range(0,sites):

                diff_re = 0
                diff_im = 0

                for l in range(0,times):
                    function_matrix_real1 .append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
                    #function_matrix_imag1 .append(function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])
                    function_matrix_real2 .append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
                    #function_matrix_imag2 .append(function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])

                    val = (function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6]-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),6])
                    diff_re = diff_re + val*val/times

#                     val = (function_matrix1[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7]-function_matrix2[int(i+j*2*bands+r*4*bands*bands+l*4*bands*bands*sites),7])
#                     diff_im = diff_im + val*val/times
                    


                grid(True)
                plot(time_dmn, function_matrix_real1, 'bo-')
                #plot(time_dmn, function_matrix_imag1, 'ok')
                plot(time_dmn, function_matrix_real2, '.r-')
                #plot(time_dmn, function_matrix_imag2, '+r')

                function_matrix_real1  = []
                function_matrix_imag1  = []
                function_matrix_real2  = []
                function_matrix_imag2  = []

            legend((filename1, filename2), 'upper right', shadow=False, fancybox=False, prop={'size':16})

                #f.text(0.2,0.75,'diff Re =' + str(diff_re))
                #f.text(0.2,0.70,'diff Im =' + str(diff_im))

                #legend(('Re '+filename1, 'Im '+filename1,'Re '+filename2, 'Im '+filename2), 'upper right', shadow=True, fancybox=True)

            savefig('./pictures/' + function_name + '/overview'+FIGURE_EXTENSION)
                
            function_matrix_real1  = []
            function_matrix_imag1  = []
            function_matrix_real2  = []
            function_matrix_imag2  = []

def plot_spectrum(domains, function_name, function_matrix1, function_matrix2):

    r_freq_dmn = domains["Pade_real_frequency_domain"]

    if os.path.exists('./pictures/' + function_name):
        shutil.rmtree('./pictures/' + function_name)
    os.makedirs('./pictures/' + function_name)

    freqs = max(function_matrix1[:,0]) + 1;

    f_real1 = []
    f_real2 = []

#     for i in range(0,bands):
#         for j in range(0,bands):
    for l in range(0,freqs): 
        f_real1.append(function_matrix1[int(l),1])
        f_real2.append(function_matrix2[int(l),1])
                     
    figure(num=None)
                    
    grid(True)
    plot(r_freq_dmn, f_real1, 'b-', label='A(w) '+filename1)
    plot(r_freq_dmn, f_real2, 'g-', label='A(w) '+filename2)

    legend(loc='upper right', shadow=False, fancybox=False, prop={'size':16})

    xlim(-8, 8)
    
    savefig('./pictures/' + function_name + '/'+function_name+FIGURE_EXTENSION)
    
    f_real1 = [] 
    f_real2 = [] 


print '\n \t start reading ' + filename1  + ' \n'


file1 = open(filename1, 'r')

function_names = []

domains_data = ''

for line in file1:

    if not ("\"functions\" " in line):
        domains_data = domains_data + line
    else:
        #domains_data_stri = domains_data[0:len(domains_data)-2] + '}'
        domains_data_stri = domains_data[0:len(domains_data)-2] + "\"tmp\" : 1 }"

        domains = json.loads(domains_data_stri)

        for line in file1:

            if "\"name\" : " in line:

                function_name = read_function_name(line)

                if(function_name == 'Self_Energy'  
                   or function_name == 'Self_energy_real_axis'
                   or function_name == 'spectral_density'
                   or function_name == 'cluster_greens_function_G_r_t'
                   or function_name == 'cluster_greens_function_G_k_t'):
                #yes_or_no = raw_input('\n\t do you want to plot ' + function_name + '? (y/n) : ')
                    
                #if(yes_or_no == 'y'):
                    
                    print function_name

                    datamatrix = [[]]
                    
                    stringmatrix = read_function_matrix(file1)
                    functiondata = json.loads(stringmatrix)
                    datamatrix   = matrix(functiondata["data"])

                    file2 = open(filename2, 'r')
                    
                    for line2 in file2:
                        if function_name in line2:
                            print line2
                            break
                        
                    datamatrix2 = [[]]
                            
                    stringmatrix2 = read_function_matrix(file2)
                    functiondata2 = json.loads(stringmatrix2)
                    datamatrix2   = matrix(functiondata2["data"])
                            
                    if(function_name == 'Self_Energy'
                       or function_name == 'cluster_greens_function_G_k_w'
                       or function_name == 'cluster_greens_function_G_r_w'
                       or function_name == 'free_cluster_greens_function_G0_k_w'
                       or function_name == 'M_r_w_function'
                       or function_name == 'M_k_w_function'
                       or function_name == 'cluster_excluded_greens_function_G0_k_w'):
                        plot_wn_function(domains, function_name, datamatrix, datamatrix2)
                            
                    if(function_name == 'cluster_greens_function_G_k_t'
                       or function_name == 'free_cluster_greens_function_G0_k_t'
                       or function_name == 'cluster_greens_function_G_r_t'
                       or function_name == 'free_cluster_greens_function_G0_k_t'
                       or function_name == 'cluster_excluded_greens_function_G0_r_t'
                       or function_name == 'cluster_hybridization_F_k_t'
                       or function_name == 'cluster_hybridization_F_r_t'):
                        plot_tau_function(domains, function_name, datamatrix, datamatrix2)

                    if(function_name == 'band-structure'):
                        plot_band_structure(domains, function_name, datamatrix, datamatrix2)

                    if(function_name == 'leading_eigenvector'):
                        plot_leading_eigenvector(domains, function_name, datamatrix, datamatrix2)

                    if(function_name == 'phi_dependent_S_k_PCM_w'):
                        plot_phi_wn_function(domains, function_name, datamatrix, datamatrix2)

                    if(function_name == 'spectral_density'):
                        plot_spectrum(domains, function_name, datamatrix, datamatrix2)

                    if(function_name == 'cluster_greens_function_G_k_w_real_axis' 
                       or function_name == 'cluster_greens_function_G0_k_w_real_axis'
                       or function_name == 'cluster_greens_function_G_r_w_real_axis' 
                       or function_name == 'cluster_greens_function_G0_r_w_real_axis'
                       or function_name == 'Self_energy_real_axis'):
                        plot_w_function(domains, function_name, datamatrix, datamatrix2)
                else:
                    if os.path.exists('./pictures/' + function_name):
                        shutil.rmtree('./pictures/' + function_name)

