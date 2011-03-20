class TestMapper(pyramid.PythonMapper):
        def mapNote(self, port, note):
                try:
                        print "Called mapNote: ", port, " ", note.channel, " ", note.note, " ", note.velocity, " ", note.state
                        note.velocity = 3
                                               
                        self.sendNote(1, note)
                except:
                        print "Unexpected error:", sys.exc_info()[0]
	def mapControl(self, port, cv):
		try:
			print "Called mapControl: ", port, " ", cv.channel, " ", cv.control, " ", cv.value
			self.sendControl(1, cv)
		except:
			print "Unexpected error:", sys.exc_info()[0]
not gonna compile
 
m = TestMapper()
m.selectPorts("1 => 'VirMIDI 2-0', 0 <= 'VirMIDI 2-1'")
