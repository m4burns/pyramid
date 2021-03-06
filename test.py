class TestMapper(pyramid.PythonMapper):
	ctr = 0
	sends = {}
	def mapNote(self, port, note):
		try:
			print "Called mapNote: ", port, " ", note.channel, " ", note.note, " ", note.velocity, " ", note.state
			if note.state == 1:
				self.ctr += 1
				self.ctr %= 8
				self.sends[note.note] = note.note + self.ctr
				note.note += self.ctr
			else:
				note.note = self.sends[note.note]
			self.sendNote(0, note)
		except:
			print "Unexpected error:", sys.exc_info()[0]

m = TestMapper()
m.selectPorts("0 => 'VirMIDI 3-0', 2 <= 'LPK25 - LPK25 MIDI 1'")

