# -*- coding: utf-8 -*-
from __future__ import print_function
import argparse
import os
import stat
import sys

# find the import for catkin's python package - either from source space or from an installed underlay
if os.path.exists(os.path.join('/opt/ros/kinetic/share/catkin/cmake', 'catkinConfig.cmake.in')):
    sys.path.insert(0, os.path.join('/opt/ros/kinetic/share/catkin/cmake', '..', 'python'))
try:
    from catkin.environment_cache import generate_environment_script
except ImportError:
    # search for catkin package in all workspaces and prepend to path
<<<<<<< HEAD
    for workspace in "/opt/ros/kinetic".split(';'):
=======
    for workspace in "/home/eee/lingfei_ws/agv/devel;/home/eee/catkin_ws/devel_isolated/rplidar_ros;/home/eee/catkin_ws/install_isolated;/home/eee/catkin_ws/devel;/opt/ros/kinetic".split(';'):
>>>>>>> 3eee1f35c09e103efb42b088a3fb81e897c89ae1
        python_path = os.path.join(workspace, 'lib/python2.7/dist-packages')
        if os.path.isdir(os.path.join(python_path, 'catkin')):
            sys.path.insert(0, python_path)
            break
    from catkin.environment_cache import generate_environment_script

code = generate_environment_script('/home/eee/lingfei_ws/agv/devel/env.sh')

output_filename = '/home/eee/lingfei_ws/agv/build/catkin_generated/setup_cached.sh'
with open(output_filename, 'w') as f:
    #print('Generate script for cached setup "%s"' % output_filename)
    f.write('\n'.join(code))

mode = os.stat(output_filename).st_mode
os.chmod(output_filename, mode | stat.S_IXUSR)
